const crypto = require('crypto')
const knexMain = require('knex')(require('./knexDatabase'))

/*
knexMain.on( 'query', function( queryData ) {
    console.log( queryData );
});
*/


module.exports = {
	/*
  createUser ({ username, password }) {
    console.log(`Add user ${username}`)
	
    return knex('user').where({ username })
      .then(([user]) => {
        if (user) return { success: false }
        const { salt, hash } = saltHashPassword({ password })
		return knex('user').insert({
		  salt,
		  encrypted_password: hash,
		  username
		})
      })
	
    
	
  },
  authenticate ({ username, password }) {
    console.log(`Authenticating user ${username}`)
    return knex('user').where({ username })
      .then(([user]) => {
        if (!user) return { success: false }
        const { hash } = saltHashPassword({
          password,
          salt: user.salt
        })
        return { success: hash === user.encrypted_password }
      })
  },
  */
  
  getGame ({ gameid }) {
	console.log(`Getting Game Image ${gameid}`)
    //return Promise.resolve()	
	
	return new Promise(function (resolve, reject) {
		knexMain.select('HeaderImage').from('Game').where( 'GameID', gameid ).orWhere( 'GameName', gameid)
		.catch(function(error) {
		  reject(error);
		})
		.then(function(Game){
			if (Game && Game[0] && Game[0]['HeaderImage'])
			{
				var image = Game[0]['HeaderImage']
				resolve(image)
			}		  	  
	  })		
	})
  },
  
  getPlayersGames ({ steamid }) {
	
	console.log(`Getting Games of ${steamid}`)
	return new Promise(function (resolve, reject) {
		var temp = "PlayerID=AES_ENCRYPT( " + steamid + ", " + "'6R*#cL&tP!b6'" + ")"
		knexMain.select('HeaderImage').from('Game').innerJoin('GamesOwned', 'GamesOwned.GameID', 'Game.GameID').whereRaw(temp)
		.catch(function(error) {
		  return reject(error);
		})
		.then(function(Game){
			resolve(Game)			
	  })		
	})
  }
}

function saltHashPassword ({
  password,
  salt = randomString()
}) {
  const hash = crypto
    .createHmac('sha512', salt)
    .update(password)
  return {
    salt,
    hash: hash.digest('hex')
  }
}

function randomString () {
  return crypto.randomBytes(4).toString('hex')
}