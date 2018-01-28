init_socket();

var socket;

//Dcdr.Interconnect.DcdrFlatBuffers.CommanderRequestData.CommanderGetSurfaceInfoRequest
function send_commander_request(requestBuilder)
{
    var builder = new flatbuffers.Builder(64);

    var request = requestBuilder(builder);

    Dcdr.Interconnect.DcdrFlatBuffers.CommanderRequest.startCommanderRequest(builder);
    Dcdr.Interconnect.DcdrFlatBuffers.CommanderRequest.addRequestDataType(builder, request.type)
    Dcdr.Interconnect.DcdrFlatBuffers.CommanderRequest.addRequestData(builder, request.value);    
    var commanderRequest = Dcdr.Interconnect.DcdrFlatBuffers.CommanderRequest.endCommanderRequest(builder);

    Dcdr.Interconnect.DcdrFlatBuffers.Parcel.startParcel(builder);
    Dcdr.Interconnect.DcdrFlatBuffers.Parcel.addParcelDataType(builder, Dcdr.Interconnect.DcdrFlatBuffers.ParcelData.CommanderRequest)
    Dcdr.Interconnect.DcdrFlatBuffers.Parcel.addParcelData(builder, commanderRequest);    
    var parcel = Dcdr.Interconnect.DcdrFlatBuffers.Parcel.endParcel(builder);

    builder.finish(parcel);

    var flatBuffersBuffer = builder.asUint8Array();

    var blob = new Blob([flatBuffersBuffer]);

    socket.send(blob);
}

function send_image_info_request()
{
    send_commander_request(function(flatBufferBuilder) {
        Dcdr.Interconnect.DcdrFlatBuffers.CommanderGetSurfaceInfoRequest
            .startCommanderGetSurfaceInfoRequest(flatBufferBuilder);
        var getSurfaceInfoRequest = Dcdr.Interconnect.DcdrFlatBuffers.CommanderGetSurfaceInfoRequest
            .endCommanderGetSurfaceInfoRequest(flatBufferBuilder);

        return {
            value: getSurfaceInfoRequest,
            type: Dcdr.Interconnect.DcdrFlatBuffers.CommanderRequestData.CommanderGetSurfaceInfoRequest,
        }
    })
}

function send_image_request()
{
    send_commander_request(function(flatBufferBuilder) {
        Dcdr.Interconnect.DcdrFlatBuffers.CommanderGetSurfaceRequest
            .startCommanderGetSurfaceRequest(flatBufferBuilder);
        var getSurfaceRequest = Dcdr.Interconnect.DcdrFlatBuffers.CommanderGetSurfaceRequest
            .endCommanderGetSurfaceRequest(flatBufferBuilder);

        return {
            value: getSurfaceRequest,
            type: Dcdr.Interconnect.DcdrFlatBuffers.CommanderRequestData.CommanderGetSurfaceRequest,
        }
    })
}

function init_commander()
{
    send_image_info_request()
    send_image_request();
}


function process_commander_get_image_info_response(imageInfo)
{
    document.getElementById("ImageInfo").textContent = 
        "width  = " + imageInfo.width() + "; " +
        "height = " + imageInfo.height();
}

function process_commander_get_image_response(image)
{
    document.getElementById("ImageInfo").textContent += "; Fromat = " + String(image.format());

    var imageArray = image.bufferArray();

    var imageBlob = new Blob([imageArray], {'type': 'image/jpeg'});
    console.log("Blob size: " + imageBlob.size);

    var url = URL.createObjectURL(imageBlob);

    var img = new Image;
    img.src = url;

    var canvas = document.getElementById("Image"); 
    canvas.width = 1376 / 2;
    canvas.height = 768 / 2;
    
    var context = canvas.getContext('2d');    

    img.onload = function() {
        context.drawImage(img, 0, 0, canvas.width, canvas.height); // Or at whatever offset you like
    };    
}

function process_commander_response(response)
{
    if (response.responseDataType() == Dcdr.Interconnect.DcdrFlatBuffers.CommanderResponseData.CommanderGetSurfaceInfoResponse)
    {
        process_commander_get_image_info_response(response.responseData(new Dcdr.Interconnect.DcdrFlatBuffers.CommanderGetSurfaceInfoResponse()));
    } else if (response.responseDataType() == Dcdr.Interconnect.DcdrFlatBuffers.CommanderResponseData.CommanderGetSurfaceResponse)
    {
        process_commander_get_image_response(response.responseData(new Dcdr.Interconnect.DcdrFlatBuffers.CommanderGetSurfaceResponse()));
    }
}

function process_parcel(parcel)
{
    if (parcel.parcelDataType() == Dcdr.Interconnect.DcdrFlatBuffers.ParcelData.CommanderResponse)
    {
        process_commander_response(parcel.parcelData(new Dcdr.Interconnect.DcdrFlatBuffers.CommanderResponse()));
    }
}

function process_message(message)
{
    var fileReader     = new FileReader();
    fileReader.onload  = function(progressEvent) {
        rawArray  = new Uint8Array(this.result);
        flatBuffer = new flatbuffers.ByteBuffer(rawArray);
        process_parcel(Dcdr.Interconnect.DcdrFlatBuffers.Parcel.getRootAsParcel(flatBuffer));
    };
    fileReader.readAsArrayBuffer(message.data);
}

function process_error()
{
    alert("No connection!");
}

function init_socket()
{
    socket = new WebSocket("ws://localhost:8080");
    socket.binaryType = "blob";    
    socket.onopen = init_commander;
    socket.onerror = process_error;
    socket.onmessage = process_message;
}