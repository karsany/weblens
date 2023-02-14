import fs from 'fs';

console.log("================================================");
console.log("indexhtml.cpp building started");

var template = fs.readFileSync('indexhtml.cpp.template', 'utf-8');
var content = fs.readFileSync('dist/index.html', 'utf-8');

var result = template.replace("{{index_html}}", content);

fs.writeFile("../src/indexhtml.cpp", result, () => { });

console.log("indexhtml.cpp written successfully");
console.log("================================================");
