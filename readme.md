# Windows ini Node C++ 扩展

基于 Windows API 开发的 ini Node C++ 扩展

# 接口

- `String setPath(String:Path)`  
  设置 ini 路径
- `String:Path getPath()`  
  获取 ini 路径
- `String:Value read(String:Section, String:Key)`  
  读取值
- `Boolean:Success write(String:Section, String:Key, String:value)`  
  设置值
- `Boolean:Success remove(String:Section[, String:Key])`  
  移除 Key 或 Section
- `Array:Keys keys(String:Section)`  
  获取 Section 所有 Key
- `Array:Sections sections()`  
  获取 ini 所有 section

>[示例](./example/demo.js)

# 编译

需安装 node-gyp 编译工具。[详细步骤](https://github.com/nodejs/node-gyp#on-windows)

然后配置编译
```bash
node-gyp configure
```
再编译工程
```bash
node-gyp build
```
