const express = require('express')
const jose = require('jose')
const nodeJose = require('node-jose');
const fetch = require('node-fetch')
const fs = require('fs');
const ms = require('ms');

function parseJwt (token) {
    try {
        var base64Url = token.split('.')[1];
        var base64 = base64Url.replace(/-/g, '+').replace(/_/g, '/');
        return JSON.parse(atob(base64));
    } catch {
        return "";
    }
};

const app = express()
app.use(express.json());

const domain = process.env.DOMAIN;

const keyStore = nodeJose.JWK.createKeyStore();

// Make sure we save the keys to disk to I can generate my own tokens while no one is watching..
if (!fs.existsSync("./Keys.json")) {
    // Generate our keys to disk
    keyStore.generate("RSA", 2048, { alg: "RS256", use: "sig" }).then((result) => {
        fs.writeFileSync(
            "Keys.json",
            JSON.stringify(keyStore.toJSON(), null, "  ")
        );
        fs.writeFileSync(
            "Keys.private.json",
            JSON.stringify(keyStore.toJSON(true), null, "  ")
        );
    });
} else {
    // Load keys from disk
    var key = JSON.parse(fs.readFileSync("Keys.private.json").toString());
    keyStore.add(key.keys[0])
        .then(res => {
            console.log("Added keys");
        })
        .catch(err => {
            console.log(err);
            console.log("Failed to import keys from disk.");
            process.exit(1);
        });
}

app.get('/jwks', async (req, res) => {
    res.send(keyStore.toJSON());
});

app.post('/login', async (req, res) => {
    if (!req.body.jwt) {
        return res.json("no token provided :(");
    }

    try {
        var jwtPayload = parseJwt(req.body.jwt);
        if (!jwtPayload.jku) {
            return res.json("JKU claim is missing");
        }
        if (jwtPayload.jku.match(new RegExp(domain)) == null) {
            return res.json("That's not our JKU. Nice try script kiddie.");
        }
    } catch {
        return res.json("Invalid JWT token");
    }

    try {
        var response = await fetch(jwtPayload.jku);
        var jwks = await response.json();
    } catch(err) {
        if (err.type == "invalid-json") {
            return res.json("Invalid json in JWKS");
        }
        return res.json("Undefined error with JKU, is it down?");
    }

    try {
        const keyStore = await nodeJose.JWK.asKeyStore(JSON.stringify(jwks));
        return nodeJose.JWS.createVerify(keyStore).
            verify(req.body.jwt).
            then(function(result) {
                if (jwtPayload.admin && jwtPayload.admin == true) {
                    return res.json({"admin": true, flag: process.env.FLAG});
                } else {
                    return res.json({"admin": false});
                }
            }).catch((err) => {
                return res.json("JWT signed with a token that's not ours. Nice try.");
            });
    } catch {
        return res.json("JWT verification failed unexpectedly.");
    }
});

app.get('/', async (req, res) => res.send(`
Welcome to my test implementation of using JWKS!<br /><br />
The endpoints are:<br />
<pre>GET  /jwks  -> returns a list with the public keys <br /></pre>
<pre>GET  /token -> Generates a token<br /></pre>
<pre>POST /login -> <b>Verifies that your token is from us</b> and tells you if you're an admin or not<br /></pre>
<pre>POST tokens as json with this format: {'jwt':'token....'}<br/></pre>
The few libraries I needed for this was: expressjs, node-fetch, and node-jose!
<br />
That's all, pretty simple right? Though you might be wondering how I get my own admin tokens. Well, that's a secret ;)
`));

app.get("/token", async (req, res) => {
    const [key] = keyStore.all({ use: "sig" });
    const opt = { compact: true, jwk: key, fields: { typ: "jwt" } };

    const payload = JSON.stringify({
        exp: Math.floor((Date.now() + ms("1d")) / 1000),
        iat: Math.floor(Date.now() / 1000),
        sub: "test",
        admin: false,
        jku: "http://"+domain+":"+process.env.PORT+"/jwks"

    });

    const token = await nodeJose.JWS.createSign(opt, key).update(payload).final();
    res.send({ token });
});

app.listen(process.env.PORT, () => {
    console.log(`App listening on port ${process.env.PORT}`)
})
