var mode_change = 1;
var mode_unchange = 0;
// create the jstree of the searching item.
function handle_jstree(goid)
{
	if(goid[0] == '^')		//处理从主页跳转进来的识别码
		goid = goid.substr(1);
	var xmlhttp2 = new XMLHttpRequest();
	xmlhttp2.onreadystatechange=function()
	{
		if(xmlhttp2.readyState==4 && xmlhttp2.status==200)
		{
			var Tstr = xmlhttp2.responseText;
			var group = new Array();
			console.log(Tstr);
			group = Tstr.split("##");//分组, 共3组, 每组格式: type, children1, children2...

			var str1 = new Array();
			var str2 = new Array();
			var str3 = new Array();
			str1 = group[0].split('@@');
			str2 = group[1].split('@@');
			str3 = group[2].split('@@');

			$('#jstree').data('jstree', false).empty().jstree({
				'core' : {
					'data' : [
					{
						'text' : str1.shift(),
						'state' : { 'opened' : true},
						'children' : str1
					},
					{
						'text' : str2.shift(),
						'state' : { 'opened' : true},
						'children' : str2
					},
					{
						'text' : str3.shift(),
						'state' : { 'opened' : true},
						'children' : str3
					}
					]
				}

			})
			
		}
	}
	xmlhttp2.open("POST", "SearchHandle.php?q=" + goid, true);
	xmlhttp2.send();
}

function handle(mode)
{
	var xmlhttp = new XMLHttpRequest();
	var temp = document.getElementById("ee").value;
	if(mode == mode_change)
		handle_jstree(temp);	
	document.getElementById("ee").value = "";
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			document.getElementById("Rcontnet").innerHTML=xmlhttp.responseText;
		}
	}

	xmlhttp.open("POST", "try.php?q=" + temp, true);
	xmlhttp.send();
}
//获取上一个页面的参数函数
function  showvalf(){  
	var thisURL = document.URL;    
	var getval =thisURL.split('?')[1];  
	var showval= getval.split("&")[0]; 
	showval = showval.split('=')[1];
	document.getElementById('ee').value = '^' + showval; 	//%->^ 避免%[A-F]产生的特殊字符
	handle(mode_change);
}  

function handle_selected(tt)
{
	var str = new Array();
	str = tt.split(' ');
	document.getElementById("ee").value = str.shift();
	// alert(document.getElementById("ee").value);
	handle(mode_unchange);
}

function showlayer(){
	$('#testMaxmin').on('click',  function(){    
		$.layer({
			type: 1,
			shade: [0],
			area: ['auto', 'auto'],
			title: false,
			border: [0],
			page: {dom : '.layer_notice'}
		});
	});
}