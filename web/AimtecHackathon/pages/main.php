<?php
  include($path_private.'pages/menu.php');
?>

<main role="main">

  <style>
  #myVideo {
    position: fixed;
    right: 0;
    bottom: 0;
    min-width: 100%;
    min-height: 100%;
  }
  .content {
    position: fixed;
    bottom: 0;
    background: rgba(0, 0, 0, 0.5);
    color: #f1f1f1;
    width: 100%;
    max-width:100%;
    padding: 20px;
  }

  .jumbotron {
    width: 100%;
    padding:0px;
  }
  </style>

  <div class="jumbotron">
    <video autoplay muted loop id="myVideo">
      <source src="video/intro.mp4" type="video/mp4">
    </video>
    <div class="container content">
      <h1 class="display-3"><img src="img/logo.png" alt="logo"></h1>
    </div>
  </div>

</main>
