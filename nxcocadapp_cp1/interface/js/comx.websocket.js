var iosocket = false;
var is_closed  = true;

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

function GenerateGUIDImpact()
{
    var guid = "";
    for (var i = 1; i <= 32; i++){
        var n = Math.floor(Math.random()*16.0).toString(16);
        guid +=   n;
    }
    return guid;
}
exports.UUID2 = GenerateGUIDImpact;

function do_nothing_cb(data)
{
    //comx.ui.InformationBox('nothing: ' + JSON.stringify(data));
}

function sleep(n)
{
    var start=new Date().getTime();
    while(true) if(new Date().getTime()-start>n) break;
}

exports.Stop = function(){
    var ret = exports.Invoke('exit', {});

    if(!ret)
    {
	sleep(500);
    }
};

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

var message_callback_map = new Object();

exports.on = function(method_name, cb)
{
    if(cb == undefined)
    {
	comx.ui.InformationBox("callback function can't be null!");
    }
    message_callback_map[method_name] = cb;
};

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
