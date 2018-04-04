const express = require('express')
const bodyParser = require('body-parser')
const store = require('./store')
const app = express()
app.use(express.static('public'))
app.use(express.static('node_modules'));

app.use(bodyParser.json())
app.post('/createUser', (req, res) => {
  store
    .createUser({
      username: req.body.username,
      password: req.body.password
    })
    .then(({ success }) => {
      if (success) res.sendStatus(200)
      else res.sendStatus(401)
    })
})

app.post('/login', (req, res) => {
  store
    .authenticate({
      username: req.body.username,
      password: req.body.password
    })
    .then(({ success }) => {
      if (success) res.sendStatus(200)
      else res.sendStatus(401)
    })
})

/*
app.post('/getGame', (req, res) => {
  store
    .getGame({
      gameid: req.body.gameid,
    })
    .then(data => {		
		console.log(data)
		res.status(200).send(data)
    })
})


app.get('/getGame', (req, res) => {
  store
    .getGame({
      gameid: req.body.gameid,
    })
    .then(data => {		
		console.log(data)
		res.status(200).send(data)
    })
})
*/
app.get('/getGame', function(req, res) {
    store
    .getGame({
      gameid: req.param('id'),
    })
    .then(data => {		
		console.log(data)
		res.send(data)
    })
});

app.get('/getGames', function(req, res) {
    store
    .getGames()
    .then(data => {		
		res.send(JSON.stringify(data));
    })
});

app.get('/getAssocationRules', function(req, res) {
    store
    .getAssocationRules({
      gameid: req.param('id'),
    })
    .then(data => {		
		res.send(JSON.stringify(data));
    })
});

app.get('/getPlayersGames', function(req, res) {
    store
    .getPlayersGames({
      steamid: req.param('id'),
    })
    .then(data => {		
		//console.log(data)
		res.send(JSON.stringify(data));
    })
});

app.get('/getPlayerCountCountry', function(req, res) {
    store
    .getPlayerCountryAmount({
      gameid: req.param('id'),
    })
    .then(data => {		
		//console.log(data)
		res.send(JSON.stringify(data));
    })
});

app.get('/getPlayerCountryPercent', function(req, res) {
    store
    .getPlayerCountryPercent({
      gameid: req.param('id'),
    })
    .then(data => {		
		//console.log(data)
		res.send(JSON.stringify(data));
    })
});

app.get('/getPlayerCountryPercentDifference', function(req, res) {
    store
    .getPlayerPercentageDifference({
      gameid: req.param('id'),
    })
    .then(data => {		
		//console.log(data)
		res.send(JSON.stringify(data));
    })
});

app.get('/getPlayerCountDay', function(req, res) {
    store
    .getPlayerAmountDay({
      gameid: req.param('id'),
    })
    .then(data => {		
		//console.log(data)
		res.send(JSON.stringify(data));
    })
});

app.get('/getRulePercentage', function(req, res) {
    store
    .getRulePercentage()
    .then(data => {		
		//console.log(data)
		res.send(JSON.stringify(data));
    })
});

app.get('/getbigplayerstatus', function(req, res) {
    store
    .getBigPlayersStatus()
    .then(data => {		
		//console.log(data)
		res.send(JSON.stringify(data));
    })
});

app.post('/startbigplayers', (req, res) => {
  store
    .startBigPlayers()
    .then(data => {	
		res.status(200).send(data)
    })
})

app.post('/stopbigplayers', (req, res) => {
  store
    .stopBigPlayers()
    .then(data => {	
		res.status(200).send(data)
    })
})

app.get('/test', function(req, res) {
  store
    .recommendGames({
		steamid: req.param('id'),
	})
    .then(data => {	
		res.send(JSON.stringify(data));
    })
})

app.listen(80, () => {
  console.log('Server running on http://localhost:80')
})