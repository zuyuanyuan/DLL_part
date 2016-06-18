/////////////////////////////////////////////////////////////////////////////////////////////////
// Import external javascript module by reqire function.

var websocket = require('socket.io/comx.websocket.js');
var runningLog = "Y:\\nxcocadapp\\data\\Running.log";//log file
var messageQueue = "Y:\\nxcocadapp\\data\\MessageQueue.log";//message queue

/////////////////////////////////////////////////////////////////////////////////////////////////
//System Pre-define functions 
var port = 30000;

var g_listener_flag = false;

function SetupClientListener()
{
    if(g_listener_flag)
    {
        return;
    }
    
    g_listener_flag = true;
    /*if(comx.sys.IsNamespaceExist('dksclient', 'comm'))
    {
        SetTimeout(1000, function(nID){
            if(binding.connect_btn_enable == 'true')
            {
                KillTimeout(nID);
                g_listener_flag = false;
                return;
            }
            
            var list = dksclient.comm.GetSolveList();

            if(list)
            {
                var list_arr = list.split(',');
                
                var task_num = list_arr.length / 2;
                
                for(var loop = 0; loop < task_num; ++loop)
                {
                    var channel = list_arr[loop];
                    var filename = list_arr[task_num + loop];

                    binding.bdf_fname = filename;
                    OnSolve(channel);
                    dksclient.comm.LockChannel(channel);
                }
            }
            //dksclient.comm.SetFinishFlag(list.split(',')[0]);
            //dksclient.comm.SetFinishFlag(list.split(',')[1]);
        });
    }*/
}

function OnInitializeData()
{
    //websocket.Startup(websocket.IsDebug()/*debug_mode*/);
    //websocket.Startup(true);
    websocket.StartupDeamon(port, websocket.IsDebug());
    //Create log file
    comx.sys.CreateFileHandler('runningLog', runningLog);
    comx.file.runningLog = Date() + "\n";
    //comx.file.runningLog = '';
    comx.sys.CloseFileHandler('runningLog');
    //Create message queue
    comx.sys.CreateFileHandler('messageQueue', messageQueue);
    comx.file.messageQueue = "";
    comx.sys.CloseFileHandler('messageQueue');
    //comx.ui.InformationBox("initialize finished");
}

function OnInitializePost()
{
}

function OnAnimate()
{
}

function OnCloseForm()
{
    var deamonmgr_json_fpath = comx.sys.GetEnvironmentVariables('NXCOCADAPP') + 'data/deamonmgr.json';
 
    comx.sys.CreateFileHandler('deamonmgr_json', deamonmgr_json_fpath);
    comx.file.deamonmgr_json = JSON.stringify({'ip' : binding.ip});
    comx.sys.CloseFileHandler('deamon_json');
    //comx.sys.RemoveFile(runningLog);
    //comx.sys.RemoveFile(messageQueue);
    websocket.Stop();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Input your javascript codes here.
websocket.on('OnWebsocketInit', function(data){
    //test--------------------------------------------
    //comx.ui.InformationBox('NXCoCadApp main.js on OnWebsocketInit'); 
    var deamonmgr_json_fpath = comx.sys.GetEnvironmentVariables('NXCOCADAPP') + 'data/deamonmgr.json';
    
    if(comx.sys.IsFileExist(deamonmgr_json_fpath))
    {
        comx.sys.CreateFileHandler('deamonmgr_json', deamonmgr_json_fpath);
        var obj = JSON.parse(comx.file.deamonmgr_json);
        comx.sys.CloseFileHandler('deamon_json');
        
        binding.ip = obj.ip;
    }
    
    ConnectToDeamonMgr();
});


function ConnectToDeamonMgr()
{
    //test--------------------------------------------
    //comx.ui.InformationBox('dksclient main.js ConnectToDeamonMgr'); 
    if(!binding.ip)
    {
        //binding.status = '输入IP地址连接，或自动搜索云服务器';
        //binding.connect_btn_enable = true;
        //binding.search_btn_enable = true;
        binding.status = '连接失败';
        return;
    }
    binding.status = '连接中, 请稍候...';
    websocket.Invoke('ConnectToDeamonMgr', {'ip':binding.ip}, function(data){
        if(data.parameters.flag)
        {
            binding.status = '连接就绪，准备协同';  
            //binding.connect_btn_enable = false;
            //binding.search_btn_enable = false;
            //binding.ip_input_enable = false;
            
            binding.ip = data.parameters.ip_address;
            
            SetupClientListener();
        }
        else
        {
            binding.status = '连接失败，等待、更换服务器重连或自动搜索';
            //binding.connect_btn_enable = true;
            //binding.search_btn_enable = true;
            //binding.ip_input_enable = true;
        }
    });
}

function OnSearch()
{
   binding.status = '搜索中, 请稍候...';

   websocket.Invoke('SearchDeamonMgr', {}, function(data){
       binding.stack_index = 0;
       if(data.parameters.ip)
       {
           binding.ip = data.parameters.ip;
           ConnectToDeamonMgr();
       }
       else
       {
           binding.status = '搜索失败，等待、更换服务器重连或再次搜索';
           //binding.connect_btn_enable = true;
           //binding.search_btn_enable = true;
           //binding.ip_input_enable = true;
       }
   });
}
