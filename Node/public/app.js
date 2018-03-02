const CreateUser = document.querySelector('.CreateUser')
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
  post('/getGame', { gameid })
    .then(({ status }) => {
      if (status === 200) alert('get image')
      else alert('login failed')
    })
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