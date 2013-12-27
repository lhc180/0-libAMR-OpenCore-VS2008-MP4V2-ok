document.write("本站文章除注明转载外，均为本站原创、整理或编译.所有文章欢迎任");
document.write("何形式的转载，但请注明作者及出处，尊重他人劳动成果！<br/>");
document.write("若您对转载的文章（作者、来源、版权）有任何疑问，请告");
document.write("知，一定即时处理（abuse{at}rosoo.net）。<br/>");
document.write("Some Rights Reserved 1998 - 2006  <a href='http://www.rosoo.net'><font face='Verdana, Arial, Helvetica, sans-serif' size='1'><b>Rosoo<font color='#CC0000'>.Net</font></b></font></a><br/>");
document.write("Except where otherwise noted, content on this site is<br/>");
document.write("licensed base <a href='http://creativecommons.org/licenses/by-nc-sa/1.0/deed.en'>a Creative Commons Attribution 2.5 License</a>");
document.write("<br/>");
document.write("<br/>");
document.write("流媒体开发 QQ群1：8655372");
document.write("<br/>");
document.write("流媒体开发 QQ群2：117013601");

function nocopy()
{
//document.selection.empty();
//alert("nocopy");
//return false;
//    if (window.clipboardData) {
  //      setTimeout(nocopy(){
    //        var text = clipboardData.getData("text");
      //      if (text && text.length > 300) {
        //        text = text + "\r\n\n本文来自罗索工作室，转载请标明出处：" + location.href;
          //      clipboardData.setData("text", text);
           // }
//        }, 100);
//    }
}

function returnfalse()
{
	return false;
}

//document.oncontextmenu=returnfalse;
//document.ondragstart=returnfalse;
//document.onselectstart =returnfalse;
//document.onselect=nocopy;
document.oncopy=nocopy;
//document.onbeforecopy=returnfalse;
//document.onmouseup=nocopy;

document.oncopy=function(){
	if (window.clipboardData) {
		setTimeout(function() {
			var text = clipboardData.getData("text");
			if (text && text.length > 300) {
				text = text + "\r\n\n本文来自罗索工作室，转载请标明出处：" + location.href;
				clipboardData.setData("text", text);
			}
		}, 100);
	}
}