//const db = require("diskdb");
const {MongoClient} = require("mongodb");
const express = require("express");
const app = express();
app.use(express.urlencoded());

const mongoUrl = 'mongodb://spooktober:S3CureP4ssw0000rd@mongo';
const client = new MongoClient(mongoUrl);
app.use(express.static('assets'));
async function main() {

    app.get('/', (req, res) => {
        return res.sendFile(__dirname+'/views/index.html');
    });
    app.get('/clients', (req, res) => {
        return res.sendFile(__dirname+'/views/clients.html');
    });


    app.post('/clients', async (req, res) => {
        console.log("Searching");
        await client.connect();
        console.log("Connected");
        var db = client.db("MonsterAuction");
        var col = db.collection("clients");
        if (!req.body) {
            return res.json("No query provided");
        }
        console.log(req.body);

        col.find(req.body, {
            projection: {
                _id: 0,
                location: 0
            }}).toArray((err, result) => {
            if (err) {
                console.log(err);
                return res.status(404).json("Not found");
            }
            return res.status(200).json(result)
        })
    });
    app.listen(3000, () => {});
}

main()
  .then(console.log)
  .catch(console.error)
  .finally(() => client.close());
