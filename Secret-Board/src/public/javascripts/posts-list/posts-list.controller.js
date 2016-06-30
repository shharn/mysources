angular
	.module('postsListModule')
		.controller('postsListController',
				['$scope', '$state', 'post', 'auth', function($scope, $state, post, auth){
					$scope.user = post.user;
					$scope.currentPageNumber = 1;
					$scope.newPost = function(){
						$state.go('newpost', {userid: $scope.user._id});
					};
					
					$scope.logOut = function(){
						auth.logOut();
					};
				}]
		);
