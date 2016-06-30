angular
	.module('postModule')
		.factory('post', ['$http', 'auth', function($http, auth){
			var obj = {
					user : {},
			};
			
			obj.getPosts = function(userid){
				return $http.get('/' + userid + '/posts', 
						{headers: {Authorization: 'Bearer ' + auth.getToken()}})
						.success(function(data){
							angular.copy(data, obj.user);
				});
			};
			
			obj.addPost = function(title, body){
				var data = {};
				data.title = title;
				data.body = body;
				data.date = Date.now();
				return $http.post('/' + obj.user._id + '/posts/newpost', data, 
						{ headers: {Authorization: 'Bearer ' + auth.getToken()}})
						.success(function(data){
							obj.user = data;
						});
			};
			
			return obj;
		}]);
