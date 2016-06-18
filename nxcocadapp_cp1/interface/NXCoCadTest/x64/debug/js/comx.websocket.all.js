var SYNV_CMD_METHOD_ID = '642AE2E9-E1FE-455F-B470-F2CBE5B870FB';
var SANDBOX_METHOD_ID = '658DC6DB-6237-4B12-A8BA-6232E94D5E2A';

var iosocket = false;
var is_closed  = true;
var cmd_mode = false;

function GenerateGUID()
{
    var guid = "";
    for (var i = 1; i <= 32; i++){
        var n = Math.floor(Math.random()*16.0).toString(16);
        guid +=   n;
        if((i==8)||(i==12)||(i==16)||(i==20))
            guid += "-";
    }
    return guid;
}
exports.UUID = GenerateGUID;

function do_nothing_cb(data)
{
    //comx.ui.InformationBox('nothing: ' + JSON.stringify(data));
}

function StartNodeJSService(debug_mode)
{
    if(comx.shell.IsCurrentWebSocketServiceValid() == "false")
    {
        var websocket_port = comx.shell.GenerateWebsocketPort();
        var unit_env = unit.name.toUpperCase();

	if(comx.sys.GetEnvironmentVariables(unit_env) == undefined)
	{
	    alert('Environment Variable - "'+unit_env+ "\" isn\'t exist");
	    pane.Close();
	    return;
	}

        var cmd = comx.sys.GetEnvironmentVariables("COMX_SDK") + "nodejs\\node.exe " +
            comx.sys.GetEnvironmentVariables(unit_env) + "js\\websocket.js " + websocket_port + " " + debug_mode + " " + comx.sys.GetEnvironmentVariables(unit_env);

	if(cmd_mode == true)
	    cmd = "cmd.exe /k " + cmd;
        comx.shell.run(cmd , !debug_mode);
    }
    else
    {
        comx.ui.InformationBox("This Form is MainWindow, Please don't Use it as Popup Sub-Dialog");
        pane.Close();
    }
}

function StartNodeJSDeamon(port, debug_mode)
{
    if(comx.shell.IsWebSocketPortValid(port) == 'true')
    {
	comx.ui.InformationBox("The Port(" + port + ") is being Used, the Deamon can't be established!");
	return false;
    }

    var unit_env = unit.name.toUpperCase();

    if(comx.sys.GetEnvironmentVariables(unit_env) == undefined)
    {
	alert('Environment Variable - "'+unit_env+ "\" isn\'t exist");
	return false;
    }

    var cmd = comx.sys.GetEnvironmentVariables("COMX_SDK") + "nodejs\\node.exe " +
        comx.sys.GetEnvironmentVariables(unit_env) + "js\\websocket.js " + port + " " + debug_mode + " " + comx.sys.GetEnvironmentVariables(unit_env);

    if(cmd_mode == true)
	cmd = "cmd.exe /k " + cmd;
    comx.shell.run(cmd , !debug_mode);

    return true;
}

function sleep(n)
{
    var start=new Date().getTime();
    while(true) if(new Date().getTime()-start>n) break;
}

exports.ConnectToNodeJS_ = function()
{
    //comx.ui.InformationBox('connecting...');
    var websocket_port = comx.shell.GetCurrentWebSocketPort();
    iosocket = io.connect("ws://localhost:" + websocket_port);

    if(!iosocket)
    {
	comx.ui.InformationBox("WebSocket Service Failed, Please Try to Restart Program!");
	pane.Close();
	return;
    }

    iosocket.on('connect', function(con_var){
        iosocket = con_var;
	iosocket.send('8155B128FEB843578D40A499E7C9DB33');
        is_closed = false;
	for(var loop = 0; loop < wait_invoke_queue.length; ++loop)
	{
	    exports.Invoke(wait_invoke_queue[loop].method_name, wait_invoke_queue[loop].parameters, wait_invoke_queue[loop].callback);
	}
	wait_invoke_queue = [];
    });

    iosocket.on('disconnect', function(){
	//comx.ui.InformationBox("close");
	pane.Close();
        is_closed = true;
    });

    iosocket.on('message', function(data){
	//comx.ui.InformationBox('main.window.ws.message received');
	var json_content = JSON.parse(data);

	if(json_content.methodid == SYNV_CMD_METHOD_ID)
	{
	    if(typeof(sync_cmd_callback_map[json_content.method]) == 'function')
	    {
		g_bIsSyncLock = true;
		sync_cmd_callback_map[json_content.method](json_content);
		g_bIsSyncLock = false;
	    }
	    return;
	}

        if(json_content.methodid != undefined)
        {
            var callback = callback_map_from_guid_to_fn[json_content.methodid];
            if(typeof(callback) == 'function')
            {
                callback(json_content);
            }
        }
        if(json_content.method != undefined)
        {
            var msg_cb = message_callback_map[json_content.method];
            if(typeof(msg_cb) == 'function')
            {
                msg_cb(json_content);
            }
        }
    });

    exports.on('error', function(data){
	var msg = 'Web Socket Error: ' + "[" + data.parameters.message + "]!";
	comx.ui.InformationBox(msg);
    });
    exports.on('GetMainWidowGID', function(data){
	data.paramerts = {'pid' : comx.shell.GetCurrentProcessPID()};
	exports.send(data);
    });
}

function ConnectToNodeJS()
{
    //if(comx.shell.IsCurrentWebSocketServiceValid() == "false")
    {
	comx.gf.mainwindow_formid = pane.formid;
	comx.ui.PopupSystemModalForm("0xe3a9309d-0x3dd1-0x4424-0x91-0xe1-0x94-0xb7-0xd3-0xc9-0x30-0xd2");
    }

    /*
    var websocket_port = comx.shell.GetCurrentWebSocketPort();
    iosocket = io.connect("ws://localhost:" + websocket_port);

    if(!iosocket)
    {
	comx.ui.InformationBox("WebSocket Service Failed, Please Try to Restart Program!");
	pane.Close();
	return;
    }

    iosocket.on('connect', function(con_var){
        iosocket = con_var;
        is_closed = false;
	for(var loop = 0; loop < wait_invoke_queue.length; ++loop)
	{
	    exports.Invoke(wait_invoke_queue[loop].method_name, wait_invoke_queue[loop].parameters, wait_invoke_queue[loop].callback);
	}
	wait_invoke_queue = [];
    });

    iosocket.on('disconnect', function(){
	//comx.ui.InformationBox("close");
	pane.Close();
        is_closed = true;
    });

    iosocket.on('message', function(data){
        var json_content = JSON.parse(data);
        if(json_content.methodid != undefined)
        {
            var callback = callback_map_from_guid_to_fn[json_content.methodid];
            if(typeof(callback) == 'function')
            {
                callback(json_content);
            }
        }
        if(json_content.method != undefined)
        {
            var msg_cb = message_callback_map[json_content.method];
            if(typeof(msg_cb) == 'function')
            {
                msg_cb(json_content);
            }
        }
    });

    exports.on('error', function(data){
	var msg = 'Web Socket Error: ' + "[" + data.parameters.message + "]!";
	comx.ui.InformationBox(msg);
    });
    //comx.ui.InformationBox(cnt);
    */
}

/*
function OnDisconnect()
{
    if(typeof(iosocket) == 'object' && is_closed != true)
    {
	iosocket.dispose();
    }
}
*/

function OnWebSocketMessage(data)
{
    //nothing
}

function PostWebSocketMessage(data)
{
    if(is_closed == false && typeof(iosocket) == 'object')
    {
	//nothing.
    }
}

exports.EnableCmdMode = function(flag)
{
    cmd_mode = flag;
};

exports.Startup = function(debug_mode){
    StartNodeJSService(debug_mode);
    ConnectToNodeJS();
};

exports.StartupDeamon = function(port, debug_mode){
    if(StartNodeJSDeamon(port, debug_mode))
    {
	comx.gf.deamon_port = port;
	comx.gf.mainwindow_formid = pane.formid;
	comx.ui.PopupSystemModalForm("0xe8eda9c0-0x7415-0x44ef-0xa1-0x49-0x29-0x3c-0xe6-0xe6-0x9c-0xbd");
    }
    else
    {
	pane.Close();
    }
};

exports.Stop = function(){
    //var json_cmd = {"method" : "exit", "methodid" : "-", "parameters" : {}};
    /*
    if(!is_closed)
    {
        iosocket.send(JSON.stringify(json_cmd));
    }
    */

    var ret = exports.Invoke('exit', {});

    if(!ret)
    {
	sleep(500);
    }
};

var g_connect_to_cb = false;

exports.ConnectTo = function(port, cb, exit_cb){
    iosocket = io.connect("ws://localhost:" + port);

    if(!iosocket)
    {
	return;
    }
    is_closed = false;
    if(typeof(cb) == 'function')
    {
	cb();
    }



    iosocket.on('disconnect', function(){
	is_closed = true;
	if(typeof(exit_cb) == 'function')
	{
	    exit_cb();
	}
    });

    iosocket.on('message', function(data){
	var json_content = JSON.parse(data);

	if(json_content.method == '5C640BD73B194AEF858398878CFEFEA4')
	{
	    //iosocket.send('8155B128FEB843578D40A499E7C9DB33');
	    if(g_connect_to_cb)
	    {
		g_connect_to_cb();
	    }
	    return;
	}

	if(json_content.methodid == SYNV_CMD_METHOD_ID)
	{
	    if(typeof(sync_cmd_callback_map[json_content.method]) == 'function')
	    {
		g_bIsSyncLock = true;
		sync_cmd_callback_map[json_content.method](json_content);
		g_bIsSyncLock = false;
	    }
	    return;
	}

        if(json_content.methodid != undefined)
        {
            var callback = callback_map_from_guid_to_fn[json_content.methodid];
            if(typeof(callback) == 'function')
            {
                callback(json_content);
            }
        }
        if(json_content.method != undefined)
        {
            var msg_cb = message_callback_map[json_content.method];
            if(typeof(msg_cb) == 'function')
            {
                msg_cb(json_content);
            }
        }

    });
};

exports.ConnectToEx = function(ip_address, port){
    iosocket = io.connect("ws://" + ip_address + ":" + port);

    if(!iosocket)
    {
	return false;
    }

    is_closed = false;

    iosocket.on('disconnect', function(){
	is_closed = true;
    });

    iosocket.on('message', function(data){
	//comx.ui.InformationBox(data);
        var json_content = JSON.parse(data);

	if(json_content.methodid == SYNV_CMD_METHOD_ID)
	{
	    if(typeof(sync_cmd_callback_map[json_content.method]) == 'function')
	    {
		g_bIsSyncLock = true;
		sync_cmd_callback_map[json_content.method](json_content);
		g_bIsSyncLock = false;
	    }
	    return;
	}

        if(json_content.methodid != undefined)
        {
            var callback = callback_map_from_guid_to_fn[json_content.methodid];
            if(typeof(callback) == 'function')
            {
                callback(json_content);
            }
        }
        if(json_content.method != undefined)
        {
            var msg_cb = message_callback_map[json_content.method];
            if(typeof(msg_cb) == 'function')
            {
                msg_cb(json_content);
            }
        }

    });
    return true;
};

exports.Connect = function(){
    if(comx.shell.IsCurrentWebSocketServiceValid() == "false")
    {
        comx.ui.InformationBox("WebSocket service don't startup,please run mainwindow\nwith WebSocket service firstly!");
	iosocket = false;
	pane.Close();
    }

    var websocket_port = comx.shell.GetCurrentWebSocketPort();

    iosocket = io.connect("ws://localhost:" + websocket_port);

    if(!iosocket)
    {
	return;
    }

    is_closed = false;



    iosocket.on('disconnect', function(){
	is_closed = true;
    });

    iosocket.on('message', function(data){
	//comx.ui.InformationBox(data);
        var json_content = JSON.parse(data);

	if(json_content.methodid == SYNV_CMD_METHOD_ID)
	{
	    if(typeof(sync_cmd_callback_map[json_content.method]) == 'function')
	    {
		g_bIsSyncLock = true;
		sync_cmd_callback_map[json_content.method](json_content);
		g_bIsSyncLock = false;
	    }
	    return;
	}

        if(json_content.methodid != undefined)
        {
            var callback = callback_map_from_guid_to_fn[json_content.methodid];
            if(typeof(callback) == 'function')
            {
                callback(json_content);
            }
        }
        if(json_content.method != undefined)
        {
            var msg_cb = message_callback_map[json_content.method];
            if(typeof(msg_cb) == 'function')
            {
                msg_cb(json_content);
            }
        }

    });
};

exports.Dispose = function(){
    //if(typeof(iosocket) == 'object' && is_closed != true)
    if(iosocket)
    {
	iosocket.dispose();
    }
};

exports.Emit = function(data){
    if(is_closed == false && typeof(iosocket) == 'object')
    {
        iosocket.send(data);
    }
};

exports.send = function(data){
    if(is_closed == false && typeof(iosocket) == 'object')
    {
        iosocket.send(JSON.stringify(data));
    }
};

var callback_map_from_guid_to_fn = new Object();

var wait_invoke_queue = [];

exports.Invoke = function(method_name, parameters, callback)
{
    if(is_closed == true)
    {
	wait_invoke_queue.push({"method_name" : method_name, "parameters" : parameters, "callback" : callback});
	return false;
    }

    if(is_closed == false && typeof(iosocket) == 'object')
    {
        var json_content = {"method" : method_name, "methodid" : GenerateGUID(), "parameters" : parameters};
	if(callback != undefined)
            callback_map_from_guid_to_fn[json_content.methodid] = callback;
	else
	    callback_map_from_guid_to_fn[json_content.methodid] = do_nothing_cb;
        iosocket.send(JSON.stringify(json_content));
    }

    return true;
};

var g_bIsSyncLock = false;

exports.IsSyncLock = function()
{
    return g_bIsSyncLock;
}

exports.CmdSync = function(method_name, parameters)
{
    if(is_closed == false && typeof(iosocket) == 'object')
    {
	//comx.ui.InformationBox(JSON.stringify(g_bIsSyncLock));
        var json_content = {"method" : method_name, "methodid" : SYNV_CMD_METHOD_ID, "parameters" : parameters};
        iosocket.send(JSON.stringify(json_content));
    }

    return true;
};

var g_sandbox_id = false;

exports.BeginSandbox = function(port, id, fn)
{
	g_sandbox_id = id;
	
	g_connect_to_cb = function()
	{
		var json_content = {"method" : "BeginSandbox", "methodid" : SANDBOX_METHOD_ID, "parameters" : {'id' : g_sandbox_id}};
		iosocket.send(JSON.stringify(json_content));
		
		if(fn)
		{
			fn();
		}
	};
	
	exports.ConnectTo(port);

    return true;
}

exports.EndSandbox = function()
{
	if(g_sandbox_id)
	{
		if(is_closed == false && typeof(iosocket) == 'object')
		{
		//comx.ui.InformationBox(JSON.stringify(g_bIsSyncLock));
			var json_content = {"method" : "EndSandbox", "methodid" : SANDBOX_METHOD_ID, "parameters" : {'id' : g_sandbox_id}};
			iosocket.send(JSON.stringify(json_content));
			
			callback_map_from_guid_to_fn[json_content.methodid] = 
			function(data)
			{
				if(data.method_name == "EndSandbox")
				{
					exports.Dispose();
				}
			}
		}
	}
	
    return true;
}

var message_callback_map = new Object();

exports.on = function(method_name, cb)
{
    if(cb == undefined)
    {
	comx.ui.InformationBox("callback function can't be null!");
    }
    message_callback_map[method_name] = cb;
};

var sync_cmd_callback_map = new Object();

exports.onCmdSync = function(method_name, cb)
{
    if(typeof(cb) == 'function')
    {
	sync_cmd_callback_map[method_name] = cb;
    }
}

exports.ConnectToCmdSrv = function(ip_address, port)
{
    exports.Invoke('F331FB3422DC4D7BBC4603593E9A8493', {'ip_address' : ip_address, 'port' : port});
}

exports.InvokeSandbox = function(formid,cache,fn)
{
	exports.Invoke('SANDBOX_AFAA50AF19704C0BA55E4D74735068B9', {'unit_name' : unit.name, 'formid' : formid, 'cache' : websocket.CacheJSON(cache), 'port' : comx.shell.GetCurrentWebSocketPort(), 'id' : websocket.UUID()}, fn);
}

exports.DisconnectFromCmdSrv = function()
{
    exports.Invoke('821681791CBC4C0A9B64F10E3E73E5A3', {});
}

exports.GetHomeDir = function()
{
	return comx.sys.GetEnvironmentVariables(unit.name.toUpperCase());
}

exports.CacheJSON = function(data){
	var cache_fname = exports.UUID().split('-').join('');
	cache_fname = exports.GetHomeDir() + 'data/' + cache_fname + '.json';
	
	comx.sys.CreateFileHandler('cache_fname', cache_fname);
	comx.file.cache_fname = JSON.stringify(data);
	comx.sys.CloseFileHandler('cache_fname');
	
	return cache_fname.split('\\').join('/');
}

exports.DetachCache = function(cache_fname){
	if(comx.sys.IsFileExist(cache_fname))
	{
		comx.sys.RemoveFile(cache_fname);
	}
}

exports.ParseCache = function(cache_fname)
{
	comx.sys.CreateFileHandler('cache_fname', cache_fname);
	var cache_str = comx.file.cache_fname;
	comx.sys.CloseFileHandler('cache_fname');
	
	return JSON.parse(cache_str);
}

exports.IsDebug = function(){
    var env_val = comx.sys.GetEnvironmentVariables('COMX_WSD_LEVEL');

    if(env_val == '1' || env_val == '2')
    {
	return true;
    }
    else
    {
	return false;
    }
    
};
