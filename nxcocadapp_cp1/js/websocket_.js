/////////////////////////////////////////////////////////////////////////////////////////////////
// Please don't modified the following codes at any time.

var port = parseInt(process.argv[2]);
var debug = JSON.parse(process.argv[3]);
var home_dir = process.argv[4];
var root_dir = process.env['COMX_SDK'];

process.chdir(home_dir + 'js/');

var websocket = require(root_dir + 'js/socket.io/websocket.common.js');

//websocket.start(port, debug);

//Code from dksclient
//console.log(websocket);
var deamon = websocket.InitDeamon();
//console.log(deamon);
var is_init = false;
function OnInit()
{
    //test--------------------------------------------
    //comx.ui.InformationBox('dksclient websocket.js OnInit'); 
    if(!is_init)
    {
        is_init = true;
        websocket.InvokeLocal('OnWebsocketInit', {}, function(data){
        });
    }
}
websocket.start(port, debug, OnInit);
//Code from dksclient

websocket.on("exit", function(data){
    process.exit();
});

process.on('uncaughtException', function (err) {
    console.error(err.stack);
    //console.log("Node NOT Exiting...");
    websocket.InvokeLocal('error', {"message" : err.message});
});

/////////////////////////////////////////////////////////////////////////////////////////////////
// Append your codes here please.
websocket.on('Test', function(data){

    data.parameters.ret = "hello,nodejs";

    websocket.send(data);

    websocket.Invoke('InvokeTest', {'res' : 'wwwwwwwwww'}, function(data){

    });

});

//ConnectToDeamonMgr
websocket.on('ConnectToDeamonMgr', function(data){
    deamon.Open(data.parameters.ip, 
        '0x86d51be5-0x4254-0x4848-0x88-0xf2-0xb5-0x8a-0x62-0x04-0xfb-0x79', 
        true, 
        function(flag){
            data.parameters = {'flag' : flag, 'ip_address' : deamon.GetCurrentAddress()};
            websocket.send(data);
        }
    ); 
});

//SearchDeamonMgr
function GetMinIP(ip_list)
{
    var ret = ip_list[0];
    for(var loop = 0; loop < ip_list.length; ++loop)
    {
        if(ip_list[loop] < ret)
        {
            ret = ip_list[loop];
        }
    }
    
    return ret;
}

websocket.on('SearchDeamonMgr', function(data){
    websocket.SearchDeamonManager(function(ip_list){
        if(ip_list)
        {
            data.parameters = {'ip' : GetMinIP(ip_list)};
        }
        else
        {
            data.parameters = {'ip' : false};
        }
        websocket.send(data);
    });
});