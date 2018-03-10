<div class="container">
  <h1 class="display-3">CarConnect</h1>
  <div class="row mb-2">
    <div class="col-md-6">
      <h2 class="display-5">Aktuální poloha:</h2>
      <div id="map"></div>
    </div>
    <div class="col-md-6">
      <h2 class="display-5">Aktuální data ze senzoru:</h2>

      <div class="card">
        <div class="card-body">
          <h3 class="display-7">Poloha</h4>
          <p id="locationID">Aktualizuji data...</p>
        </div>
      </div>

      <p>&nbsp;</p>

      <div class="card">
        <div class="card-body">
          <h3 class="display-7">Natočení</h4>
          <p id="turnID">Aktualizuji data...</p>
        </div>
      </div>

      <p>&nbsp;</p>

      <div class="card">
        <div class="card-body">
          <h3 class="display-7">Akcelerace</h4>
          <p class="accelerationID">Aktualizuji data...</p>
        </div>
      </div>

    </div>
  </div>
</div>


<script>
  var map;
  function initMap() {
    map = new google.maps.Map(document.getElementById('map'), {
      center: {lat: 49.740598, lng: 13.367352},
      zoom: 18
    });
  }

  var marker;
  var myPosition;

  function getLocation() {
    if (navigator.geolocation) {
      navigator.geolocation.getCurrentPosition(showPosition);
    } else {
      alert("Geolocation is not supported by this browser.");
    }
  }

  function showPosition(position) {
    var lat = position.coords.latitude;
    var lng = position.coords.longitude;

    myPosition = new google.maps.LatLng(lat, lng)

    map.setCenter();

    marker = new google.maps.Marker({
           position: myPosition,
           animation: google.maps.Animation.DROP,
           map: map,
           title: 'Our position',
           icon: "img/man.png"
         });
  }

  getLocation();

  $(document).ready(function() {

setInterval(function() {
  $.ajax({
   type: "GET",
   url: "http://192.168.90.218",
   data: "",
   success: function(msg){
     $("#turnID").text(msg);
   }
 });
}, 1000);

});

</script>
<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyDU_AILMGzN6CZd-92HMrDXCYsAcidva-8&callback=initMap" async defer></script>
