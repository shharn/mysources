angular
	.module('postsListModule')
		.controller('postsListController',
				['$scope', '$state', '$stateParams', 'post', 'auth', function($scope, $state, $stateParams, post, auth){
					$scope.user = post.user;
					$scope.currentPage = $stateParams.pagenum;
					$scope.pageArr = post.pageArr;
					$scope.newPost = function(){
						$state.go('newpost', {userid: $scope.user._id});
					};	
					
					$scope.isPrevExist = function(){
						return ($scope.currentPage / 10) > 1;
					};
					
					$scope.isNextExist = function(){
						return ($scope.pageArr[$scope.pageArr.length - 1] * 10 < ($scope.user.numberPosts));
					};
					
					$scope.changePage = function(pageNum){
						$state.go('userhome', {userid:$scope.user._id, pagenum:pageNum});
					};
					
					$scope.goPost = function($index){
						$state.go('post', {userid:$scope.user._id, pagenum:$scope.currentPage, postIndex:$index});
					};
					
					$scope.logOut = function(){
						auth.logOut();
					};
				}]
		)
		.controller('NavController',
				['$scope', '$state', 'post', 'auth', function($scope, $state, post, auth){
					$scope.currentUser = auth.currentUser();
				
					$scope.logOut = function(){
						auth.logOut();
						$state.go('home');
					};
				}]);
