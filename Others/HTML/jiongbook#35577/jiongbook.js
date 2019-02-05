var c=document.getElementById("myCanvas");
var cxt=c.getContext("2d");


var max=150;
var x=30;

cxt.strokeStyle="#888ae9";
for (var i=0;i<5;i++)
{
    cxt.moveTo(max,max-x);
    cxt.lineTo(max-x,max);
    cxt.lineTo(max,max+x);
    cxt.lineTo(max+x,max);
    cxt.lineTo(max,max-x);
    cxt.stroke();
    x+=30;
}

cxt.strokeStyle="#705cce";
cxt.beginPath();
cxt.moveTo(max,0);
cxt.lineTo(max,2*max);
cxt.lineTo(max,0);
cxt.moveTo(0,max);
cxt.lineTo(2*max,max);
cxt.lineTo(0,max);
cxt.stroke();


var up=110;
var left=80;
var down=140;
var right=70;
var y1=max-up;
var x1=max-left;
var y2=max+down;
var x2=max+right;

cxt.globalAlpha=0.9;
var grd=cxt.createLinearGradient(0,0,0,y2);
grd.addColorStop(0,"#3fd6dc");
grd.addColorStop(1,"#888ae9");
cxt.fillStyle=grd;
cxt.strokeStyle='rgba(0,0,0,0)';
cxt.beginPath();
cxt.moveTo(max,y1);
cxt.lineTo(x1,max);
cxt.lineTo(max,y2);
cxt.lineTo(x2,max);
cxt.lineTo(max,y1);
cxt.stroke();
cxt.fill(0,0,2*max,2*max);

cxt.globalAlpha=1;
cxt.fillStyle="#705cce";
var r=5;
cxt.beginPath();
cxt.arc(max,y1,r,0,Math.PI*2,true);
cxt.closePath();
cxt.fill();

cxt.beginPath();
cxt.arc(x1,max,r,0,Math.PI*2,true);
cxt.closePath();
cxt.fill();

cxt.beginPath();
cxt.arc(max,y2,r,0,Math.PI*2,true);
cxt.closePath();
cxt.fill();

cxt.beginPath();
cxt.arc(x2,max,r,0,Math.PI*2,true);
cxt.closePath();
cxt.fill();