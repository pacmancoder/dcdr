//init_socket();

var socket;

//DcdrFlatBuffers.CommanderRequestData.CommanderGetSurfaceInfoRequest
function send_commander_request(requestBuilder)
{
    var builder = new flatbuffers.Builder(64);

    var request = requestBuilder(builder);

    DcdrFlatBuffers.CommanderRequest.startCommanderRequest(builder);
    DcdrFlatBuffers.CommanderRequest.addRequestDataType(builder, request.type)
    DcdrFlatBuffers.CommanderRequest.addRequestData(builder, request.value);    
    var commanderRequest = DcdrFlatBuffers.CommanderRequest.endCommanderRequest(builder);

    DcdrFlatBuffers.Parcel.startParcel(builder);
    DcdrFlatBuffers.Parcel.addParcelDataType(builder, DcdrFlatBuffers.ParcelData.CommanderRequest)
    DcdrFlatBuffers.Parcel.addParcelData(builder, commanderRequest);    
    var parcel = DcdrFlatBuffers.Parcel.endParcel(builder);

    builder.finish(parcel);

    var flatBuffersBuffer = builder.asUint8Array();

    var blob = new Blob([flatBuffersBuffer]);

    socket.send(blob);
}

function send_image_info_request()
{
    send_commander_request(function(flatBufferBuilder) {
        DcdrFlatBuffers.CommanderGetSurfaceInfoRequest
            .startCommanderGetSurfaceInfoRequest(flatBufferBuilder);
        var getSurfaceInfoRequest = DcdrFlatBuffers.CommanderGetSurfaceInfoRequest
            .endCommanderGetSurfaceInfoRequest(flatBufferBuilder);

        return {
            value: getSurfaceInfoRequest,
            type: DcdrFlatBuffers.CommanderRequestData.CommanderGetSurfaceInfoRequest,
        }
    })
}

function send_image_request()
{
    send_commander_request(function(flatBufferBuilder) {
        DcdrFlatBuffers.CommanderGetSurfaceRequest
            .startCommanderGetSurfaceRequest(flatBufferBuilder);
        var getSurfaceRequest = DcdrFlatBuffers.CommanderGetSurfaceRequest
            .endCommanderGetSurfaceRequest(flatBufferBuilder);

        return {
            value: getSurfaceRequest,
            type: DcdrFlatBuffers.CommanderRequestData.CommanderGetSurfaceRequest,
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
    if (response.responseDataType() == DcdrFlatBuffers.CommanderResponseData.CommanderGetSurfaceInfoResponse)
    {
        process_commander_get_image_info_response(response.responseData(new DcdrFlatBuffers.CommanderGetSurfaceInfoResponse()));
    } else if (response.responseDataType() == DcdrFlatBuffers.CommanderResponseData.CommanderGetSurfaceResponse)
    {
        process_commander_get_image_response(response.responseData(new DcdrFlatBuffers.CommanderGetSurfaceResponse()));
    }
}

function process_parcel(parcel)
{
    if (parcel.parcelDataType() == DcdrFlatBuffers.ParcelData.CommanderResponse)
    {
        process_commander_response(parcel.parcelData(new DcdrFlatBuffers.CommanderResponse()));
    }
}

function process_message(message)
{
    var fileReader     = new FileReader();
    fileReader.onload  = function(progressEvent) {
        rawArray  = new Uint8Array(this.result);
        flatBuffer = new flatbuffers.ByteBuffer(rawArray);
        process_parcel(DcdrFlatBuffers.Parcel.getRootAsParcel(flatBuffer));
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