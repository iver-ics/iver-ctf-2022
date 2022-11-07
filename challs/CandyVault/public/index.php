<?php
include_once "./flag.php";

$loggedIn = false;
$error = null;
if (isset($_GET['source'])) {
    highlight_file(__FILE__);
    die();
}
$bannedHashes = file(__DIR__."/bannedHashes.txt", FILE_IGNORE_NEW_LINES);
if (isset($_POST['password'])) {
    $password = $_POST["password"];
    if (in_array(md5($password), $bannedHashes)) {
        // Make sure all my leaked passwords are banned from this site so people can't hack me!
        $error = "That's a banned hash! Begone script kiddie.";
    } else if(keyvault_check($password)) {
        // Use my secure keyvault check where people will never find my password!
        $loggedIn = true;
    } else {
        $error = "Invalid password";
    }
}?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <title>Spooky Candy Vault</title>
        <meta charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-Zenh87qX5JnK2Jl0vWa8Ck2rdkQ2Bzep5IDxbcnCeuOxjzrPF/et3URy9Bv1WTRi" crossorigin="anonymous">
        <style>
            html, body {
                background: url("https://images.unsplash.com/photo-1513593854556-94df5c54a8d6?ixlib=rb-4.0.3&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=1770&q=80");
                height: 100%;
                width: 100%;
                min-height: 100%;
                min-width: 100%;
            }
        </style>
    </head>
    <body>
        <div class="container h-100">
            <div class="d-flex justify-content-center align-items-center h-100">
                <div class="w-50 card p-4">
                    <?php if ($loggedIn) { ?>
                        <h1>Candy Vault Dashboard</h1>
                        <p>All the candy at your service...</p>
                        <p>
                            Use this magic keyword for more candy
                            <span style="font-weight: bold"><?php echo $flag; ?></span>
                        </p>
                    <?php } else { ?>
                        <h1>Spooktober Candy Vault</h1>
                        <p>Candy Vault. Where all halloween candy is stored. Only authorized skeletons is allowed.</p>
                        <?php if ($error) { echo "<p style='color:red'>$error</p>"; } ?>
                        <form action="" method="POST">
                            <div class="mb-3">
                                <label class="form-label" for="password">Password</label>
                                <input class="form-control" id="password" type="password" placeholder="Password" name="password" />
                            </div>
                            <button class="btn btn-primary">Logga in</button>
                        </form>
                    <?php } ?>
                </div>
            </div>
        </div>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-OERcA2EqjJCMA+/3y+gxIOqMEjwtxJY7qPCqsdltbNJuaOe923+mo//f6V8Qbsw3" crossorigin="anonymous"></script>
    </body>
</html>
