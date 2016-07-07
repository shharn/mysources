angular
	.module('newpostModule')
		.controller('newpostController', 
				['$scope', '$state', '$stateParams', '$location', 'post', 
				 function($scope, $state, $stateParams, $location, post){
					$scope.isEdit = $location.path().split("/")[4];
					$scope.post =  $scope.isEdit? post.user.posts[$stateParams.postIndex] : {};							
					$scope.submitNewPost = function(){
						if($scope.isEdit){
							post.editPost($scope.post.title, $scope.post.body, $scope.post._id)
							.then(function(){
								$state.go('userhome', {userid:post.user._id, pagenum:post.currPage});
							});
						}
						else{
							post.addPost($scope.post.title, $scope.post.body)
							.then(function(){
								$state.go('userhome', {userid:post.user._id, pagenum:post.currPage});
							});
						}
					};
					
					$scope.cancel = function(){
						$state.go('userhome', {userid:post.user._id, pagenum:post.currPage});
					}
				}]);
