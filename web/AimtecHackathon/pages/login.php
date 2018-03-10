<?php
  $error = '';

  if (isset($_POST['login'])&&isset($_POST['pass'])&&($_POST['login']=='admin@j1.cz')&&($_POST['pass']=='JedemJ1')) {
    $_SESSION['logintoken'] = 'kalijebuh';

    header('Location: index.php');
    exit();
  } else {
    if (isset($_POST['login'])) {
      $error = 'Neplatné údaje...';
    }
  }

?>

<style>
.form-signin {
max-width: 330px;
padding: 15px;
margin: 0 auto;
}
.form-signin .form-signin-heading,
.form-signin .checkbox {
margin-bottom: 10px;
}
.form-signin .checkbox {
font-weight: normal;
}
.form-signin .form-control {
position: relative;
height: auto;
-webkit-box-sizing: border-box;
        box-sizing: border-box;
padding: 10px;
font-size: 16px;
}
.form-signin .form-control:focus {
z-index: 2;
}
.form-signin input[type="email"] {
margin-bottom: -1px;
border-bottom-right-radius: 0;
border-bottom-left-radius: 0;
}
.form-signin input[type="password"] {
margin-bottom: 10px;
border-top-left-radius: 0;
border-top-right-radius: 0;
}
</style>

<?php
  if ($error != '') {
    echo('<div class="alert alert-danger">
  <strong>Error!</strong> '.$error.'
</div>');
  }
?>

<div class="container">
  <form class="form-signin" method="post">
    <h2 class="form-signin-heading">Prosím přihlašte se</h2>
    <label for="inputEmail" class="sr-only">Email</label>
    <input name="login" value="<?php echo isset($_POST['login'])? $_POST['login']:''; ?>" type="email" id="inputEmail" class="form-control" placeholder="Email address" required autofocus>
    <label for="inputPassword" class="sr-only">Heslo</label>
    <input name="pass" type="password" id="inputPassword" class="form-control" placeholder="Password" required>
    <button class="btn btn-lg btn-primary btn-block" type="submit">Přihlásit</button>
  </form>
</div> <!-- /container -->
