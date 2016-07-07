angular
	.module('postModule')
		.factory('post', ['$http', 'auth', function($http, auth){
			var obj = {
					user : {},
			};
			
			obj.getPosts = function(userid, pagenum){
				return $http.get('/' + userid + '/posts/' + pagenum, 
						{headers: {Authorization: 'Bearer ' + auth.getToken()}})
						.success(function(data){
							angular.copy(data, obj.user);
							var arr = [];
							var pageStart= (pagenum - 1) - (pagenum - 1) % 10 + 1;
							var endPage;
							
							if(data.numberPosts / 10 >= pageStart + 9 )
								endPage = pageStart + 9;
							else{
								endPage = data.numberPosts / 10;
								if(data.numberPosts % 10 > 0)
									endPage++;
							}
												
							for(var idx = pageStart; idx <= endPage; idx++)
								arr.push(idx);
							
							obj.pageArr = arr;
							obj.currPage = pagenum;
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
			
			obj.deletePost = function(postIndex){
				return $http.post('/' + obj.user._id + '/post/' + obj.user.posts[postIndex]._id +
						'/delete', null, {headers: {Authorization : 'Bearer ' + auth.getToken()}});
			};
			
			obj.editPost = function(title, body, postId){
				var data = {};
				data.title = title;
				data.body = body;
				return $http.post('/' + obj.user._id + '/post/' + postId +
						'/edit', data, {headers: {Authorization : 'Bearer ' + auth.getToken()}});
			}
			return obj;
		}]);
