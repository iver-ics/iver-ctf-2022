<?php
if(isset($_GET['source'])) {
    highlight_file(__FILE__);
    die();
}
function check_expr($expr) {
    if (strlen($expr) >= 90) { //don't DOS us please, the calculator is slow!
        return "ERROR - TOO LONG";
    } else {
        $invalid = false;
        $blacklist = [' ', '\t', '\r', '\n','\'', '"', '`', '\[', '\]'];
        foreach ($blacklist as $blacklisted) {
            if (preg_match('/' . $blacklisted . '/m', $expr)) {
                $invalid = true;
                break;
            }
        }
        //allow math functions: http://php.net/manual/en/ref.math.php
        $whitelist = [
            'abs',
            'acos',
            'acosh',
            'asin',
            'asinh',
            'atan2',
            'atan',
            'atanh',
            'base_convert',
            'bindec',
            'ceil',
            'cos',
            'cosh',
            'decbin',
            'dechex',
            'decoct',
            'deg2rad',
            'exp',
            'expm1',
            'floor',
            'fmod',
            'getrandmax',
            'hexdec',
            'hypot',
            'intdiv',
            'is_finite',
            'is_infinite',
            'is_nan',
            'lcg_value',
            'log10',
            'log1p',
            'log',
            'max',
            'min',
            'mt_getrandmax',
            'mt_rand',
            'mt_srand',
            'octdec',
            'pi',
            'pow',
            'rad2deg',
            'rand',
            'round',
            'sin',
            'sinh',
            'sqrt',
            'srand',
            'tan',
            'tanh'
        ];
        preg_match_all('/[a-zA-Z_\x7f-\xff][a-zA-Z_0-9\x7f-\xff]*/', $expr, $used_funcs);
        foreach ($used_funcs[0] as $func) {
            if (!in_array($func, $whitelist)) {
                $invalid = true;
                break;
            }
        }
        if ($invalid) {
            return "Nice try, script kiddie. Use only the allowed functions.";
        }
        try{
            return eval('return ' . $expr . ';');
        } catch (ParseError $e) {
            echo $e;
            return "ERROR - SYNTAX";
        } catch (Throwable $t) {
            echo $t;
            return "ERROR - UNKNOWN";
        }
    }
}
$expr = $_POST['expr'];
?>
<h4>Welcome to our online calcualtor!</h4>
<p>Feel free do do any calculations below. Just don't make them too long, it's somewhat slow.</p>
<p>You can also find allowed math functions here: <a href="http://php.net/manual/en/ref.math.php">PHP math functions</a></p>
<p>We're also all about open source, to view this calculators source code, go here: <a href="/?source">Source Code</a></p>
<form method="POST">
<input name="expr" value="<?php echo isset($expr) ? $expr : "sin(pi()*4)"; ?>" />
    <button>Submit</button>
</form>

<?php
if (isset($expr)) {
    echo "Calculator result: " . check_expr($expr);
    echo "<br />";
}
?>
