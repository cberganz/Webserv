const axios = require('axios')


var config = {
	method: 'get',
	url: 'http://localhost:8080',
	headers: { 
	  'Accept': 'text/html'
	//   'Accept': 'image/avif'
	}
};

function	get_formation_request()
{

	axios(config)
	.then(function (res) { 
		console.log(res.data);
	})
	.catch(err => console.log(err))
}

get_formation_request()