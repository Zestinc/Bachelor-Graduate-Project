function LayerPage(Id){
	var xmlhttp = new XMLHttpRequest();
	xmlhttp.onreadystatechange=function(){
		if(xmlhttp.readyState==4 && xmlhttp.status==200){
			var Tstr = xmlhttp.responseText;
			// alert(Tstr);
			var pageii = $.layer({
				type: 1,
				title: false,
				area: ['auto', 'auto'],
			    border: [0], //去掉默认边框
			    shade: [0], //去掉遮罩
			    closeBtn: [0, true], //去掉默认关闭按钮
			    shift: 'center', //从左动画弹出
			    page: {
			    	html: '<div style="width:420px; height: 260px; padding:20px; border:1px solid #ccc; overflow:auto; background-color:#B0E2FF;"><p>' + Tstr + '</p></div>'
			    }
			});
		}	
	}
	// alert(Id);
	xmlhttp.open("POST", "try.php?q=" + Id, true);
	xmlhttp.send();
}
