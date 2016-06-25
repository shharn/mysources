angular
	.module('newpostModule')
		.controller('newpostController', 
				['$scope', '$state', 'post', function($scope, $state, post){
					$scope.post = {};
					$scope.submitNewPost = function(){
						post.addPost($scope.post.title, $scope.post.body)
						.success(function(){
							$state.go('userhome', {userid:post.obj.userid});
						});
					};
					
					$scope.cancel = function(){
						$state.go('userhome', {userid:post.obj.userid});
					}
				}]);