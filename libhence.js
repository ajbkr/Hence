var HENCE_FALSE = '0';
var HENCE_TRUE  = '1';

var Stack = [];

var __lcall__ = function() {
    var name = 'hence_' + __pop__();
    module.exports[name]();
};

var __depth__ = function() {
    __push__(Stack.length + '');
};

var __pop__ = function() {
    var length = Stack.pop();
    var s = '';
    for (var i = 0; i < length; ++i) {
        s += String.fromCharCode(Stack.pop());
    }
    Stack.pop();	// NUL
    return s;
};

var __push__ = function(s) {
    Stack.push('\u0000'.charCodeAt());	// NUL
    for (var i = s.length - 1; i >= 0; --i) {
        Stack.push(s[i].charCodeAt());
    }
    Stack.push(s.length);
};

var hence_and = function() {
    var y = __pop__();
    var x = __pop__();
    __push__((x != HENCE_FALSE && y != HENCE_FALSE) ? (HENCE_TRUE) :
        (HENCE_FALSE));
};

var hence_call = function() {
    var x = __pop__();
    if (Functions[x]) {
        Functions[x]();
    } else {
        throw('Runtime error');
    }
};

var hence_concatenate = function() {
    var y = __pop__();
    var x = __pop__();
    __push__(y + x);
};

var hence_depth = function() {
    __depth__();
};

var hence_drop = function() {
    __pop__();
};

var hence_if = function() {
    var cond_func  = __pop__();
    var true_func  = __pop__();
    var false_func = __pop__();

    if (Functions[cond_func]) {
        Functions[cond_func]();
    } else {
        throw('Runtime error');
    }
    var result = __pop__();
    if (result != HENCE_FALSE) {
        if (Functions[true_func]) {
            Functions[true_func]();
        } else {
            throw('Runtime error');
        }
    } else {
        if (Functions[false_func]) {
            Functions[false_func]();
        } else {
            throw('Runtime error');
        }
    }
};

var hence_json_rpc = function() {
    var method = __pop__();
    var params = __pop__();
    process.stdout.write('{"method":"' + method + '","params":' + params +
        ',"id":1}' + "\n");
};

var hence_less_than = function() {
    var y = __pop__() | 0;
    var x = __pop__() | 0;
    __push__((y < x) ? (HENCE_TRUE) : (HENCE_FALSE));
};

var hence_not = function() {
    __push__((__pop__() != HENCE_FALSE) ? (HENCE_FALSE) : (HENCE_TRUE));
};

var hence_or = function() {
    var y = __pop__();
    var x = __pop__();
    __push__((x != HENCE_FALSE || y != HENCE_FALSE) ? (HENCE_TRUE) :
        (HENCE_FALSE));
};

var hence_pick = function() {
    var n = (__pop__() | 0) + 1;
    var v = [];
    for (var i = 0; i < n; ++i) {
        v.push(__pop__());
    }
    for (var i = v.length - 1; i >= 0; --i) {
        __push__(v[i]);
    }
    __push__(v[v.length - 1]);
};

var hence_print = function() {
    process.stdout.write(__pop__());
};

var hence_rotate = function() {
    var z = __pop__();
    var y = __pop__();
    var x = __pop__();
    __push__(y);
    __push__(z);
    __push__(x);
};

var hence_subtract = function() {
    var y = __pop__();
    var x = __pop__();
    __push__((x - y) + '');
};

var hence_swap = function() {
    var y = __pop__();
    var x = __pop__();
    __push__(y);
    __push__(x);
};

var hence_target = function() {
    __push__('js');
};

module.exports.__lcall__ = __lcall__;

module.exports.__depth__ = __depth__;
module.exports.__pop__   = __pop__;
module.exports.__push__  = __push__;

module.exports.hence_and         = hence_and;
module.exports.hence_call        = hence_call;
module.exports.hence_concatenate = hence_concatenate;
module.exports.hence_depth       = hence_depth;
module.exports.hence_drop        = hence_drop;
module.exports.hence_if          = hence_if;
module.exports.hence_json_rpc    = hence_json_rpc;
module.exports.hence_less_than   = hence_less_than;
module.exports.hence_not         = hence_not;
module.exports.hence_or          = hence_or;
module.exports.hence_pick        = hence_pick;
module.exports.hence_print       = hence_print;
module.exports.hence_rotate      = hence_rotate;
module.exports.hence_subtract    = hence_subtract;
module.exports.hence_swap        = hence_swap;
module.exports.hence_target      = hence_target;
