angular
	.module('postsListModule')
		.controller('postsListController',
				['$scope', 'posts', 'auth', function($scope, posts, auth){
					$scope.posts = posts;
					$scope.username = auth.username;
					$scope.logOut = function(){
						auth.logOut();
					};
				}]
		);