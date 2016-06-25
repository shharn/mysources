angular
	.module('authModule')
		.factory('auth', ['$http', '$window', function($http, $window){
			var auth = {};
			
			auth.saveToken = function(token){
				$window.localStorage['secret-board-token'] = token;
			};
			
			auth.getToken = function(){
				return $window.localStorage['secret-board-token'];
			};
			
			auth.isLoggedIn = function(){
				var token = auth.getToken();
				
				if(token){
					// JWT : { Header, Payload, Signature }
					var payload = JSON.parse($window.atob(token.split('.')[1]));
					return payload.exp > Date.now() / 1000;
				} else {
					return false;
				}
			};
			
			auth.currentUser = function(){
				if(auth.isLoggedIn()){
					var token = auth.getToken();
					var payload = JSON.parse($window.atob(token.split('.')[1]));
					return payload.username;
				}
			};
			
			auth.register = function(user){
				return $http.post('/register', user).success(function(data){
					auth.saveToken(data.token);
				});
			};
			
			auth.logIn = function(user){
				return $http.post('/login', user).success(function(data){
					auth.saveToken(data.token);
					auth.id = data._id;
					auth.name = user.username;
				});
			};
			
			auth.logOut = function(){
				$window.localStorage.removeItem('secret-board-token');
			};
			
			return auth;
		}]);