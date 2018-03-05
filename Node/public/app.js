const CreateUser = document.querySelector('.CreateUser')
/*
CreateUser.addEventListener('submit', (e) => {
  e.preventDefault()
  const username = CreateUser.querySelector('.username').value
  const password = CreateUser.querySelector('.password').value
  post('/createUser', { username, password })
    .then(({ status }) => {
      if (status === 200) alert('User Created!')
      else alert('User Name Already Exists')
    })
})
const Login = document.querySelector('.Login')
Login.addEventListener('submit', (e) => {
  e.preventDefault()
  const username = Login.querySelector('.username').value
  const password = Login.querySelector('.password').value
  post('/login', { username, password })
    .then(({ status }) => {
      if (status === 200) alert('login success')
      else alert('login failed')
    })
})

const GetGame = document.querySelector('.GetGameImage')
GetGame.addEventListener('submit', (e) => {
  e.preventDefault()
  const gameid = GetGame.querySelector('.gameid').value
  get('/getGame?id=' + gameid)
  .then(res => res.text())
	.then(body => {
		console.log(body)	
	    document.querySelector('img').src = body
	});

	
})
*/
const GetPlayerGames = document.querySelector('.GetPlayersGames')
GetPlayerGames.addEventListener('submit', (e) => {
  e.preventDefault()
  const steamid = GetPlayerGames.querySelector('.steamid').value
  get('/getPlayersGames?id=' + steamid)
  .then(res => res.text())
	.then(body => {
		var json = JSON.parse(body)
		
		var container = document.getElementById('imageContainer');
		var docFrag = document.createDocumentFragment();
		
		container.innerHTML = "";
		
		for(var exKey in json) {

			var img = document.createElement('img');
			img.src = json[exKey].HeaderImage;
			docFrag.appendChild(img);
			
			/*
			id="test" + exKey			
			var image = document.getElementById(id)
			if(image != null)
			{
				image.src = json[exKey].HeaderImage
			} 
			*/
			
		}
		
		container.appendChild(docFrag);
	});

	
})

function post (path, data) {
  return window.fetch(path, {
    method: 'POST',
    headers: {
      'Accept': 'application/json',
      'Content-Type': 'application/json'
    },
    body: JSON.stringify(data)
  })
}

function get (path, data) {
  return window.fetch(path)  
} 


