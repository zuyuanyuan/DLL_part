var websocket = require('comx.websocket.js');

var port = 30000;

websocket.ConnectTo(port, function(){
    
    websocket.Invoke('Test', {}, function(data){
	//console.Clear();
	console.log(data.parameters.ret);
    });
});

websocket.on('InvokeTest', function(data){
    console.log('Websocket服务器返回的结果是' + data.parameters.res);
    //websocket.Dispose();
    //process.exit();
});

function OnProcessExit(){
    websocket.Dispose();
}

websocket.on('SolveOpt', function(data){
	opt.SetCadParameters(data.parameters.id, data.parameters.cad_paras);
    data.parameters.res = opt.Solve(data.parameters.id);
    websocket.send(data);
});

function SaveResultAs(id, fpath)
{
	websocket.Invoke('SaveOptResultAs', {'id' : id, 'fpath' : fpath}, function(data){
	});
}

websocket.on('SetOptTaskDoneFlag', function(data){
	opt.SetDoneFlag(data.parameters.id);
});