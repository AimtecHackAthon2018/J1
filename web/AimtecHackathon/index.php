<?php
  session_start();

  // Only for debugging
  error_reporting(E_ALL);
  ini_set('display_errors', '1');

  $path_private = './';

  require_once($path_private.'function/connectDB.php');


  $page = 'login.php';

  if (isset($_SESSION['logintoken']) && ($_SESSION['logintoken']=='kalijebuh')) {
    $page = 'main.php';

    if (isset($_GET['page'])) {
      $page = preg_replace("/[^A-Za-z0-9 ]/", '', $_GET['page']).'.php';

      if (!file_exists($path_private.'pages/'.$page)) {
        $page = 'errorpage.php';
      }

    }
  }

  include($path_private.'template/top.php');
  include($path_private.'pages/'.$page);
  include($path_private.'template/bottom.php');

  require_once($path_private.'function/closeDB.php');
?>
