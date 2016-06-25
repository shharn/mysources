angular
	.module('postModule')
		.factory('post', ['$http', 'auth', function($http, auth){
			var obj = {
					posts: []
			};
			
			obj.getPosts = function(userid){
				return $http.get('/' + userid + '/posts', 
						{headers: {Authorization: 'Bearer ' + auth.getToken()}})
						.success(function(data){
							console.log("In success");
							angular.copy(data.posts, obj.posts);
							obj.totalPosts = data.totalPosts;
				});
			};
			
			obj.addPost = function(title, body){
				var data;
				var d = new Date();
				data.title = title;
				data.body = body;
				data.date = d.now();
				return $http.post('/' + obj.userid + '/posts/newpost', data, 
						{ headers: {Authorization: 'Bearer ' + auth.getToken()}})
						.success(function(res){
							obj.posts.push(data);
						});
			};
			
			return obj;
		}]);