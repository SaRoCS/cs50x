document.querySelector("#hs").onclick = function(){
    hideCo();
    hideDe();
    hideEx();
    showHs();
}
document.querySelector("#college").onclick = function(){
    hideHs();
    hideDe();
    hideEx();
    showCo();
}
document.querySelector("#degrees").onclick = function(){
    hideHs();
    hideEx();
    hideCo();
    showDe();
}
document.querySelector("#exp").onclick = function(){
    hideHs();
    hideDe();
    hideCo();
    showEx();
}

function hideHs()
{
    document.getElementById("hstitle").style.display = "none";
    document.getElementById("hscontent").style.display = "none";
    document.getElementById("hs").classList.remove("active");
}
function hideCo()
{
    document.getElementById("cotitle").style.display = "none";
    document.getElementById("cocontent").style.display = "none";
    document.getElementById("college").classList.remove("active");
}
function hideDe()
{
    document.getElementById("detitle").style.display = "none";
    document.getElementById("decontent").style.display = "none";
    document.getElementById("degrees").classList.remove("active");
}
function hideEx()
{
    document.getElementById("extitle").style.display = "none";
    document.getElementById("excontent").style.display = "none";
    document.getElementById("exp").classList.remove("active");
}

function showHs()
{
    document.getElementById("hstitle").style.display = "block";
    document.getElementById("hscontent").style.display = "block";
    document.getElementById("hs").classList.add("active");
}
function showCo()
{
    document.getElementById("cotitle").style.display = "block";
    document.getElementById("cocontent").style.display = "block";
    document.getElementById("college").classList.add("active");
}
function showDe()
{
    document.getElementById("detitle").style.display = "block";
    document.getElementById("decontent").style.display = "block";
    document.getElementById("degrees").classList.add("active");
}
function showEx()
{
    document.getElementById("extitle").style.display = "block";
    document.getElementById("excontent").style.display = "block";
    document.getElementById("exp").classList.add("active");
}

