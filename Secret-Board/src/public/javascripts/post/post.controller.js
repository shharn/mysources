angular
	.module('postModule')
		.controller('postController',
				['$scope', '$stateParams', '$state', '$window', 'post', 'auth', 
				 function($scope, $stateParams, $state, $window, post, auth){
					$scope.post = post.user.posts[$stateParams.postIndex];
					$scope.idx = $stateParams.postIndex;
					console.log("post.title : " + $scope.post.title);
					console.log("post.body : " + $scope.post.body);
					$scope.deletePost = function(){
						post.deletePost($scope.idx).success(function(msg){
							$window.alert(msg);
							$state.go('userhome', {userid:post.user._id, pagenum:post.currPage});
						});
					};
					
					$scope.editPost = function(){
						$state.go('editpost', {userid:post.user._id, pagenum:post.currPage, postIndex:$stateParams.postIndex
							, newpost:true});
					};
					
					$scope.goList = function(){
						$state.go('userhome', {userid:post.user._id, pagenum:post.currPage});
					};
				}]);
