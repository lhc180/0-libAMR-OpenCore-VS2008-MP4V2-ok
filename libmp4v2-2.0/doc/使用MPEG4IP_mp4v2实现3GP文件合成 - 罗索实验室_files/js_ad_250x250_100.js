/*
var ADcurrentURL=document.location.href;
var ADstag=ADcurrentURL.indexOf('//')+1; 
ADcurrentURL=ADcurrentURL.substring(ADstag+1,ADcurrentURL.length);
ADstag=ADcurrentURL.indexOf('/'); 
var ADdomain=ADcurrentURL.substring(0,ADstag); 



if (ADdomain=="roarsoft.net" || ADdomain == "www.roarsoft.net")
{
*/
	document.open();
	document.write("<script type='text/javascript'>");
	document.write("var cpro_id = 'u680168';");
	document.write("</script>");
	document.write("<script src='http://cpro.baidu.com/cpro/ui/c.js' type='text/javascript'></script>");
	document.close();
/*
}
else
{
	document.write("<script type='text/javascript'>");
	document.write("google_ad_client = 'pub-3349738643245862';");
	document.write("google_ad_slot = '8133459122';");
	document.write("google_ad_width = 250;");
	document.write("google_ad_height = 250;");
	document.write("</script>");
	document.write("<script type='text/javascript' src='http://pagead2.googlesyndication.com/pagead/show_ads.js'></script>");
}
*/
