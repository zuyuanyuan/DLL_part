var io = (function(){
Array.prototype.indexOf = function(val)
{              
    for (var i = 0; i < this.length; i++) {  
        if (this[i] == val) return i; 
    }  
    return -1;  
};  

Array.prototype.remove = function(val) 
{  
    var index = this.indexOf(val);  
    if (index > -1) {  
        this.splice(index, 1);  
    }  
};  

function iosocket_class(_uri)
{
    this.uri = _uri;
    this.events_entry = {};
    this.is_connected = false;
    this.on = function(type, cb)
    {
	this.events_entry[type] = cb;
    };
    
    var ret = comx.iosocket.Connect(_uri);
    if(ret == "true")
    {
	this.is_connected = true;
    }
    else
    {
	this.is_connected = false;
    }
    
    this.send = function(data)
    {
	comx.iosocket.Emit(this.uri, "message", data);
    };
    
    this.emit = function(type, data)
    {
	comx.iosocket.Emit(this.uri, type, data);
    };
    
    this.dispose = function()
    {
     io.sessions.remove(this);
     comx.iosocket.Close(this.uri);
     //comx.ui.InformationBox('dispose');
    }
}

function io_class()
{
    this.sessions = [];
    this.connect = function(uri)
    {
	var session = new iosocket_class(uri);
	if(session.is_connected == true)
	{
	    this.sessions.push(session);		
	    return session;
	}
	
	//comx.ui.InformationBox(io.sessions.length);
	
	return false;
    };
}

function iosocket_reset_item_t(uri, events_entry)
{
	this.uri = uri;
	this.events_entry = events_entry;
}

return new io_class();
})();


//var G_cur_reset_iosocket_queue = [];

// OnMessage message.
function __socket_io_E74C5F24A235457094D605A73D4B7C50(uri, json)
{
    var type = JSON.parse(json).name;

    if(!type)
    {
	type = 'message';
    }
    
    for(loop = io.sessions.length - 1; loop >= 0; --loop)
    {
	if(typeof(io.sessions[loop].events_entry[type]) == "function" &&
	   io.sessions[loop].uri == uri)
	{
	    if(type == 'connect')
	    {
		io.sessions[loop].events_entry[type](io.sessions[loop]);
	    }
	    else
	    {
		if(type == 'message')
		{
		    io.sessions[loop].events_entry[type](json);
		}
		else
		{
		    io.sessions[loop].events_entry[type](JSON.stringify(JSON.parse(json).args[0]));
		}
	    }
	    
	    /*if(type == 'disconnect')
	    {
		io.sessions[loop].dispose();
	    }*/
	}
    }
}

// OnCloseForm message.
/*
function __socket_io_5A18B046649E4df6A55E88BFC179C289()
{
    if(comx.shell.IsCurrentWebSocketServiceValid() == "false")
    {
	return;
    }

    for(loop = io.sessions.length - 1; loop >= 0; --loop)
    {
	io.sessions[loop].dispose();
    }
}
*/
// OnIdle Message
/*
function __socket_io_E8FEB401E1AA4d709B0929133EA9EDFC()
{
    for(loop = 0; loop < G_cur_reset_iosocket_queue.length; ++loop)
    {
	var __socketio = io.connect(G_cur_reset_iosocket_queue[loop].uri);
	if(__socketio != false)
	{
	    __socketio.events_entry = G_cur_reset_iosocket_queue[loop].events_entry;
	    
	    G_cur_reset_iosocket_queue.splice(loop, 1);
	    
	    return;
	}
    }
}
*/

function require(js_file)
{
    var js_path = JS_HOME_DIR + '/' + js_file;

    if(fs.existsSync(js_path) == 'false')
    {
	js_path = JS_HOME_DIR + '/js/' + js_file;
    }

    //comx.ui.InformationBox(js_path);

    //comx.ui.InformationBox(fs.existsSync(js_path));

    if(fs.existsSync(js_path) == 'false')
    {
        //comx.ui.InformationBox('failed');
	return;
    }

    var js_content = fs.readFileSync(js_path);

    //comx.ui.InformationBox(js_content);
    
    var js_cmd = "(function(){var exports = new Object();";
    js_cmd += js_content;
    js_cmd += "return exports;})();";

    return eval(js_cmd);
}
