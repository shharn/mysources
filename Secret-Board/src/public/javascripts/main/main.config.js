angular
	.module('secretBoard')
		.config(['$stateProvider', 
		         '$urlRouterProvider', 
		         function($stateProvider, $urlRouterProvider){
					$stateProvider
						.state('home', {
							url: '/home',
							templateUrl:'/views/login.html',
							controller: 'loginController',
						})
						.state('register', {
							url: '/register',
							templateUrl: '/views/register.html',
							controller: 'registerController',
						})
						.state('userhome', {
							url: '/:userid/posts',
							templateUrl: '/views/posts-list.html',
							controller: 'postsListController',
							resolve: {
								posts: ['$stateParams', 'post', function($stateParams, post){
									return post.getPosts($stateParams.userid);
								}]
							}
						});
					
					$urlRouterProvider.otherwise('home');
		}]);