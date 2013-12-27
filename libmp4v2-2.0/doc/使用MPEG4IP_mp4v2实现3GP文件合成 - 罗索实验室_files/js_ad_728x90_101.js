var ADcurrentURL=document.location.href;
var ADstag=ADcurrentURL.indexOf('//')+1; 
ADcurrentURL=ADcurrentURL.substring(ADstag+1,ADcurrentURL.length);
ADstag=ADcurrentURL.indexOf('/'); 
var ADdomain=ADcurrentURL.substring(0,ADstag); 

if (ADdomain=="roarsoft.net" || ADdomain == "www.roarsoft.net")
{
	document.open();
	document.write("<script type='text/javascript'>");
	document.write("alimama_pid=\"mm_10026851_117704_122406\";");
	document.write("alimama_titlecolor=\"0000FF\";");
	document.write("alimama_descolor =\"000000\";");
	document.write("alimama_bgcolor=\"FFFFFF\";");
	document.write("alimama_bordercolor=\"E6E6E6\";");
	document.write("alimama_linkcolor=\"008000\";");
	document.write("alimama_bottomcolor=\"FFFFFF\";");
	document.write("alimama_anglesize=\"0\";");
	document.write("alimama_bgpic=\"0\";");
	document.write("alimama_icon=\"0\";");
	document.write("alimama_sizecode=\"11\";");
	document.write("alimama_width=760;");
	document.write("alimama_height=90;");
	document.write("alimama_type=2;");
	document.write("</script>");
	document.write("<script src=\"http://a.alimama.cn/inf.js\" type=text/javascript></script>");
	document.close();	
}else{
	document.write("<script type='text/javascript'>");
	document.write("google_ad_client = 'pub-3349738643245862';");
	document.write("google_ad_slot = '2360225121';");
	document.write("google_ad_width = 728;");
	document.write("google_ad_height = 90;");
	document.write("</script>");
	document.write("<script type='text/javascript' src='http://pagead2.googlesyndication.com/pagead/show_ads.js'></script>");
}
