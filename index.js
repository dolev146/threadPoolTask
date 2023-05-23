// import fs
const fs = require("fs");

// create a file that will have the data 1,2,3,4,5....10000 in it

// create a file
fs.writeFile("data.txt", "", (err) => {
  if (err) throw err;
  console.log("File is created successfully.");
});

// write data to the file
for (let i = 1; i <= 10000; i++) {
  fs.appendFile("data.txt", i + ",", (err) => {
    if (err) throw err;
    // console.log("Data is written to file successfully.");
  });
}
