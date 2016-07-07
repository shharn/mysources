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
							url: '/:userid/posts/:pagenum',
							templateUrl: '/views/posts-list.html',
							controller: 'postsListController',
							resolve: {
									userPromise: ['$stateParams', 'post', function($stateParams, post){
										return post.getPosts($stateParams.userid, $stateParams.pagenum);
									}]
							},
						})
						.state('newpost', {
							url: '/:userid/posts/newpost/',
							templateUrl: '/views/new-post.html',
							controller: 'newpostController'
						})
						.state('post', {
							url: '/:userid/post/:pagenum-:postIndex',
							templateUrl: '/views/post.html',
							controller: 'postController'
						})
						.state('editpost', {
							url:'/:userid/post/:pagenum-:postIndex/edit',
							templateUrl: '/views/new-post.html',
							controller: 'newpostController'
						});
					
					$urlRouterProvider.otherwise('home');
		}]);
