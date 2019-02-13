let path = require('path')
let ini = require('../build/Release/ini');
let file = path.resolve(__dirname, 'tmp.ini');
let Ini = ini(file);
console.log('set ini path', file);
console.log('ini path:', Ini.getPath());
console.log('write "value" to "key" in "setting":', 
            Ini.write("setting", "key", "value"));
console.log('write "中文value" to "中文Key" in "setting":', 
            Ini.write("setting", "中文Key", "中文value"));
console.log('read "key" in "setting":', 
            Ini.read("setting", "key"));
console.log('read "中文Key" in "setting":', 
            Ini.read("setting", "中文Key"));
console.log('read "notexist" in "setting":', 
            Ini.read("setting", "notexist"));
console.log('get all keys in "setting":', 
            Ini.keys("setting"));
console.log('remove "key" in "setting":', 
            Ini.remove("setting", "key"));
console.log('get all keys in "setting":', 
            Ini.keys("setting"));
console.log('write "othervalue" to "otherKey" in "other setting":', 
            Ini.write("other section", "otherkey", "othervalue"));
console.log('get all keys in "other setting":', 
            Ini.keys("other section"));
console.log('get all sections in ini:', 
            Ini.sections());
