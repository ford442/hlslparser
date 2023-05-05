#include "HLSLParser.h"

#include "GLSLGenerator.h"
#include "HLSLGenerator.h"
#include "MSLGenerator.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <emscripten.h>

using namespace M4;

enum Target
{
    Target_VertexShader,
    Target_FragmentShader,
};

enum Language
{
	Language_GLSL,
	Language_HLSL,
	Language_LegacyHLSL,
	Language_Metal,
};

std::string ReadFile( const char* fileName )
{
	std::ifstream ifs( fileName );
	std::stringstream buffer;
	buffer << ifs.rdbuf();
	return buffer.str();
}

void PrintUsage()
{
	std::cerr << "usage: hlslparser [-h] [-fs | -vs] FILENAME ENTRYNAME\n"
		<< "\n"
		<< "Translate HLSL shader to GLSL shader.\n"
		<< "\n"
		<< "positional arguments:\n"
		<< " FILENAME    input file name\n"
		<< " ENTRYNAME   entry point of the shader\n"
		<< "\n"
		<< "optional arguments:\n"
		<< " -h, --help  show this help message and exit\n"
		<< " -fs         generate fragment shader (default)\n"
		<< " -vs         generate vertex shader\n"
		<< " -glsl       generate GLSL (default)\n"
		<< " -hlsl       generate HLSL\n"
		<< " -legacyhlsl generate legacy HLSL\n"
		<< " -metal      generate MSL\n";
}

void c_main(){
		// Parse arguments
	const char* fileName = "./shader/shader.hlsl";
	const char* entryName = "shader.hlsl";

	Target target = Target_FragmentShader;
	Language language = Language_GLSL;

	
		//	PrintUsage();
	
			target = Target_FragmentShader;
	
		//	target = Target_VertexShader;
	
			language = Language_GLSL;
	
		//	language = Language_HLSL;

		//	language = Language_LegacyHLSL;

	// Read input file
	const std::string source = ReadFile( fileName );

	// Parse input file
	Allocator allocator;
	HLSLParser parser( &allocator, fileName, source.data(), source.size() );
	HLSLTree tree( &allocator );
	if( !parser.Parse( &tree ) )
	{
		Log_Error( "Parsing failed, aborting\n" );
		return;
	}

	// Generate output
	if (language == Language_GLSL)
	{
		GLSLGenerator generator;
		if (!generator.Generate( &tree, GLSLGenerator::Target(target), GLSLGenerator::Version_140, entryName ))
		{
			Log_Error( "Translation failed, aborting\n" );
			return;
		}

		std::cout << generator.GetResult();
	}
	else if (language == Language_HLSL)
	{
		HLSLGenerator generator;
		if (!generator.Generate( &tree, HLSLGenerator::Target(target), entryName, language == Language_LegacyHLSL ))
		{
			Log_Error( "Translation failed, aborting\n" );
			return;
		}

		std::cout << generator.GetResult();
	}

}

extern"C"{

void str(){
c_main();
}

}

EM_JS(void,js_main,(),{

    "use strict";

    window.scroll(0,0);

    let $tim=document.getElementById('tim');
    let $itim=document.getElementById('itim');
    let $high=document.getElementById('canvasSize');
    let winSize=parseInt(window.innerHeight,10);
    $high.innerHTML=winSize;

    var $shds=[];

    function normalResStart(){
    document.getElementById('shut').innerHTML=2;
    document.getElementById('circle').width=window.innerWidth;
    document.getElementById('circle').height=window.innerHeight;
    document.getElementById('di').click();
    setTimeout(function(){
        document.getElementById('stat').innerHTML='Sending Start';
        document.getElementById('stat').style.backgroundColor='green';
        Module.ccall('str');
    },100);
    document.getElementById('bcanvas').width=window.innerHeight;
    document.getElementById('bcanvas').height=window.innerHeight;
    document.getElementById('scanvas').width=window.innerHeight;
    document.getElementById('scanvas').height=window.innerHeight;
    document.getElementById('acanvas').width=window.innerHeight;
    document.getElementById('acanvas').height=window.innerHeight;
    document.getElementById('di').click();
}

function shds(xml){
    const sparser=new DOMParser();
    let htmlDoch=sparser.parseFromString(xml.responseText,'text/html');
    let preList=htmlDoch.getElementsByTagName('pre')[0].getElementsByTagName('a');
    $shds[0]=preList.length;
    for(var i=1;i<preList.length;i++){
        var txxts=preList[i].href;
        var Self=location.href;
        Self=Self.replace(/1ink.1ink/,"");
        txxts=txxts.replace(Self,"");
        $shds[i+1]='https://glsl.1ink.us/hlsl/'+txxts;
    }
    let shadesNum=$shds[0];
    if(shadesNum>0){
        var randShade=1;
    };
    let shdMenu=document.getElementById('sh1');
    var path;
    if(shdMenu.value!='Default'){
        if(shdMenu.value=='Random'){
            document.getElementById('path').innerHTML=$shds[randShade];
        }else{
            document.getElementById('path').innerHTML='https://glsl.1ink.us/hlsl/'+shdMenu.value;
        }
    }else{
        var fle=document.getElementById('path').innerHTML;
        document.getElementById('path').innerHTML='https://glsl.1ink.us/hlsl/'+fle;
    }
    var pth=document.getElementById('path').innerHTML;
    const ff=new XMLHttpRequest();
    ff.open('GET',pth,true);
    ff.responseType='arraybuffer';
    document.getElementById('stat').innerHTML='Downloading Shader';
    document.getElementById('stat').style.backgroundColor='yellow';
    ff.addEventListener("load",function(){
        let sarrayBuffer=ff.response;
        if(sarrayBuffer){
            let sfil=new Uint8ClampedArray(sarrayBuffer);
            FS.writeFile('/shader/shader.hlsl',sfil);
            document.getElementById('stat').innerHTML='Downloaded Shader';
            document.getElementById('stat').style.backgroundColor='blue';
//setTimeout(function(){
            normalResStart();
//},350);
        }
    });
    ff.send(null);
}

function scanShaders(){
    const dxhttp=new XMLHttpRequest();
// dxhttp.withCredentials=false;
    dxhttp.addEventListener("load",function(){
        shds(this);
    });
    dxhttp.open('GET','https://glsl.1ink.us/shaders/',true);
    dxhttp.send();
}

let tem=document.getElementById('tim');
let ban=document.getElementById('menuBtn');
let sfr=document.getElementById('slideframe');
var $lt;
function grab$lt(){$lt=Math.round($lt);}
$lt=tem.innerHTML;grab$lt();
let slo=new Slideout({'panel':document.getElementById('panel'),'menu':document.getElementById('menu'),'padding':384,'tolerance':70,'easing':'cubic-bezier(.32,2,.55,.27)'});
ban.addEventListener('click',function(){slo.toggle();sfr.innerHTML="";
    setTimeout(function(){
        grab$lt();var slt=$lt/1000;slt=Math.round(slt);
        sfr.innerHTML='<input type='+'"te'+'xt" id'+'="time'+'slider"/'+'>';
        let tsl=new rSlider({target:'#timeslider',values:{min:0.25,max:30.00},
            step:[0.25],labels:false,tooltip:true,scale:false,});
        grab$lt();slt=($lt/1000);slt=slt*100;slt=Math.round(slt);
        slt=slt/100;tsl.setValues(slt);
        document.getElementById('menu').addEventListener('click',function(){
            var $ll=tsl.getValue();$ll=$ll*100;$ll=Math.round($ll);$ll=$ll/100;$ll=($ll*1000);tem.innerHTML=$ll;
        });
        setTimeout(function(){slt=tem.innerHTML;},8);},16);});
const pnnl=document.body;
document.getElementById('startBtn').addEventListener('click',function(){
    document.getElementById('circle').width=window.innerWidth;
    document.getElementById('circle').height=window.innerHeight;
    document.getElementById('di').click();
    document.getElementById('stat').innerHTML='Scanning Shaders';
    document.getElementById('stat').style.backgroundColor='yellow';
    scanShaders();
});
setTimeout(function(){
    document.getElementById('circle').width=window.innerWidth;
    document.getElementById('circle').height=window.innerHeight;
    document.getElementById('di').click();
},100);

function Key(e){
    if(e.code=='KeyQ'){document.getElementById('startBtn').click();};
}
pnnl.addEventListener('keydown',Key);

});

static inline void(*jss)(){&js_main};

int main(void){
using namespace M4;
EM_ASM({
FS.mkdir('/shader');
});
jss();
return 0;
}
