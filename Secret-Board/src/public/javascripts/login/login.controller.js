angular
	.module('loginModule')
		.controller('loginController', 
				['$scope', '$http', '$state', 'auth', 
				 function($scope, $http, $state, auth){
					$scope.height = window.innerHeight;
					$scope.user = {};
					$scope.logIn = function(){
						auth.logIn($scope.user).error(function(err){
							$scope.error = err;
						}).then(function(){
							$state.go('userhome', {userid: auth.id, pagenum:1});
						});			
				};
		}]);
