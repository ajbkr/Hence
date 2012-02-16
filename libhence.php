<?php
define('HENCE_FALSE', '0');
define('HENCE_TRUE',  '1');

$Stack = array();

function __lcall__()
{
    $name = 'hence_' . __pop__();
    $name();
}

function __depth__()
{
    global $Stack;

    __push__((string) count($Stack));
}

function __pop__()
{
    global $Stack;

    $length = array_pop($Stack);
    $s = '';
    for ($i = 0; $i < $length; ++$i) {
        $s .= chr(array_pop($Stack));
    }
    array_pop($Stack);	// NUL
    return $s;
}

function __push__($s)
{
    global $Stack;

    $Stack[] = ord('\0');	// NUL
    for ($i = strlen($s) - 1; $i >= 0; --$i) {
        $Stack[] = ord($s{$i});
    }
    $Stack[] = strlen($s);
}

function hence_and()
{
    $y = __pop__();
    $x = __pop__();
    __push__(($x != HENCE_FALSE && $y != HENCE_FALSE) ? (HENCE_TRUE) :
        (HENCE_FALSE));
}

function hence_call()
{
    global $Functions;

    $x = __pop__();
    if (isset($Functions[$x])) {
        $Functions[$x]();
    } else {
        file_put_contents('php://stderr', 'Runtime error' . PHP_EOL);
        exit(1);
    }
}

function hence_concatenate()
{
    $y = __pop__();
    $x = __pop__();
    __push__($y . $x);
}

function hence_depth()
{
    __depth__();
}

function hence_drop()
{
    __pop__();
}

function hence_if()
{
    global $Functions;

    $cond_func  = __pop__();
    $true_func  = __pop__();
    $false_func = __pop__();

    if (isset($Functions[$cond_func])) {
        $Functions[$cond_func]();
    } else {
        file_put_contents('php://stderr', 'Runtime error' . PHP_EOL);
        exit(1);
    }
    $result = __pop__();
    if ($result != HENCE_FALSE) {
        if (isset($Functions[$true_func])) {
            $Functions[$true_func]();
        } else {
            file_put_contents('php://stderr', 'Runtime error' . PHP_EOL);
            exit(1);
        }
    } else {
        if (isset($Functions[$false_func])) {
            $Functions[$false_func]();
        } else {
            file_put_contents('php://stderr', 'Runtime error' . PHP_EOL);
            exit(1);
        }
    }
}

function hence_json_rpc()
{
    $method = __pop__();
    $params = __pop__();
    echo '{"method":"' . $method . '","params":' . $params . ',"id":1}',
        PHP_EOL;
}

function hence_less_than()
{
    $y = (int) __pop__();
    $x = (int) __pop__();
    __push__(($y < $x) ? (HENCE_TRUE) : (HENCE_FALSE));
}

function hence_not()
{
    __push__((__pop__() != HENCE_FALSE) ? (HENCE_FALSE) : (HENCE_TRUE));
}

function hence_or()
{
    $y = __pop__();
    $x = __pop__();
    __push__(($x != HENCE_FALSE || $y != HENCE_FALSE) ? (HENCE_TRUE) :
        (HENCE_FALSE));
}

function hence_pick()
{
    $n = (int) __pop__() + 1;
    $v = array();
    for ($i = 0; $i < $n; ++$i) {
        $v[] = __pop__();
    }
    for ($i = count($v) - 1; $i >= 0; --$i) {
        __push__($v[$i]);
    }
    __push__($v[count($v) - 1]);
}

function hence_print()
{
    echo __pop__();
}

function hence_rotate()
{
    $z = __pop__();
    $y = __pop__();
    $x = __pop__();
    __push__($y);
    __push__($z);
    __push__($x);
}

function hence_subtract()
{
    $y = (int) __pop__();
    $x = (int) __pop__();
    __push__((string) ($x - $y));
}

function hence_swap()
{
    $y = __pop__();
    $x = __pop__();
    __push__($y);
    __push__($x);
}

function hence_target()
{
    __push__('php');
}
