const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
.card{
  // Formato de la clase .card
  max-width: 200px;
  min-height: 100px;
  font-size:30;
  color: #000000;
  margin:20px;
  display:flex;
  justify-content:center;
  background:#7d9182;
  align-items:center;
  box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
</style>
<body>

<h1 style="font-size:120;text-align:center;"><strong>Parqueo-matic</h1></strong>
<h2 style="font-size:60;text-align:center;"><strong>Control de registro para parqueos</h2></strong>

<div class="card">
  <h1><strong>Parqueo 1: <span id="P1"></span></strong></h1>
</div>
<div class="card">
  <h1><strong>Parqueo 2: <span id="P2"></span></strong></h1>
</div>
<div class="card">
  <h1><strong>Parqueo 3: <span id="P3"></span></strong></h1>
</div>
<div class="card">
  <h1><strong>Parqueo 4: <span id="P4"></span></strong></h1>
</div>

<script>
// Se establece el intervalo para recibir datos de la ESP32
setInterval(function() {
  getData();
}, 20);
// Se reciben los datos
function getData() {
  // Variable 1
  var xh1 = new XMLHttpRequest();
  xh1.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("P1").innerHTML =
      this.responseText;
    }
  };
  xh1.open("GET", "readP1", true);
  xh1.send();
  // Variable 2
  var xh2 = new XMLHttpRequest();
  xh2.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("P2").innerHTML =
      this.responseText;
    }
  };
  
  xh2.open("GET", "readP2", true);
  xh2.send();
  // Variable 3
  var xh3 = new XMLHttpRequest();
  xh3.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("P3").innerHTML =
      this.responseText;
    }
  };
  xh3.open("GET", "readP3", true);
  xh3.send();
  // Variable 4
  var xh4 = new XMLHttpRequest();
  xh4.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("P4").innerHTML =
      this.responseText;
    }
  };
  xh4.open("GET", "readP4", true);
  xh4.send();
}
</script>
</body>
</html>
)=====";
