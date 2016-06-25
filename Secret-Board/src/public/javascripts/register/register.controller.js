angular
	.module('registerModule')
		.controller('registerController', 
				['$scope', 
				 '$http', 
				 '$state',
				 'auth',
				 function($scope, $http, $state, auth){
					$scope.user = {};
					$scope.checkPassword = true;
					$scope.repeatedPassword = '';
					
					$scope.register = function(){
						auth.register($scope.user).error(function(error){
			 				$scope.error = error;
			 			}).then(function(){
			 				$state.go('home');
			 			});
			 		};
			 		
			 		$scope.cancel = function(){
			 			$state.go('home');
			 		};
			 		
			 		$scope.checkPswd = function($event){
			 			if($scope.user.password !== $scope.repeatedPassword)
			 				$scope.checkPassword = false;
			 			else
			 				$scope.checkPassword = true;
			 		};
			 		
				}
		]);