var fs = require('fs');

console.log("================================================");
console.log("VERSION building started");

var template = fs.readFileSync('src/version.cpp.template', 'utf-8');

var revision = require('child_process')
  .execSync('git rev-parse HEAD')
  .toString().trim().substring(0, 6);

console.log("Revision: " + revision);

var dts = ("{datetime}", new Date().toISOString());

var result = "v1.0-" + revision + " (" + dts + ")";

console.log("Version: " + result);

fs.writeFile("src/version.cpp", template.replace("{{version}}", result), () => { });

console.log("src/version.cpp written successfully");
console.log("================================================");
