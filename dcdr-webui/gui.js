
var nodes = [];
var jobs = [];
var nodeInfos = [];

addNode("ok", "192.168.1.1:13254", 1);
addNode("warning", "My node", 2);
addNode("error", "127.0.0.1:64123", 42);
addNode("unknown", "???", 4);

addJob("ok", "Spheres (1920x1080)", 1);

addNodeInfo("Test", "Info");
addNodeInfo("One", "TWOOOOOOOOOOOOOOOOOOOOOOOOO");

function addExtendedListItemItem(status, text, list) {
    var listItem = document.createElement("div");
    listItem.className = "extended-list-item";

    var ledElement = document.createElement("span");
    ledElement.className = "status-led status-led-" + status;
    ledElement.innerText = "\xa0";
    listItem.appendChild(ledElement);
    listItem.appendChild(document.createTextNode(text));

    var listElement = document.getElementById(list);
    listElement.appendChild(listItem);

    return listItem;
}


function addInfoListItem(name, value, list) {
    var listItem = document.createElement("div");
    listItem.className = "info-list-item";

    var leftPart = document.createElement("span");
    leftPart.className = "info-list-item-left info-list-item-part";
    leftPart.appendChild(document.createTextNode(name));

    var rightPart = document.createElement("span");
    rightPart.className = "info-list-item-right info-list-item-part";
    rightPart.appendChild(document.createTextNode(value));

    listItem.appendChild(leftPart);
    listItem.appendChild(rightPart);

    var listElement = document.getElementById(list);
    listElement.appendChild(listItem);

    return listElement;
}

function addNodeInfo(name, value)
{
    var nodeInfo = {};

    nodeInfo.element = addInfoListItem(name, value, "node-info-list")

    nodeInfos.push(nodeInfo);
}

function clearNodeInfos() {
    nodeInfos.forEach(function(nodeInfo){
        document.getElementById("node-info-list").removeChild(nodeInfos.element);
    });
}


function addNode(status, name, id) {
    var node = {};
    node.id = id;

    node.element = addExtendedListItemItem(status, name, "nodes-list");
    node.element.onclick = function() {onNodeClick(node)};

    nodes.push(node);
}

function clearNodes() {
    nodes.forEach(function(node){
        document.getElementById("nodes-list").removeChild(node.element);
    });
}

function onNodeClick(node) {
    alert("You clicked node:" + node.id);
}

function addJob(status, name, id) {
    var job = {};
    job.id = id;

    job.element = addExtendedListItemItem(status, name, "jobs-list");
    job.element.onclick = function() {onJobClick(job)};

    jobs.push(job)
}

function clearJobs() {
    jobs.forEach(function(job){
        document.getElementById("jobs-list").removeChild(job.element);
    });
}

function onJobClick(job) {
    alert("You clicked job:" + job.id);
}