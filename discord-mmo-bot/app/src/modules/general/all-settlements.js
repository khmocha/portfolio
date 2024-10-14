const FileSystem = require("fs");
const Path = require("path");

const DirectoryPath = Path.join(__dirname, "../settlement-objs");

const SettlementFiles = FileSystem.readdirSync(DirectoryPath);

const Settlements = {};

SettlementFiles.forEach(SettlementFile => {
    const FilePath = Path.join(DirectoryPath, SettlementFile);
    
    const SettlementObject = require(FilePath);

    Settlements[SettlementObject.Name] = SettlementObject;
});

module.exports = Settlements;