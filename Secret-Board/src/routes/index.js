var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');
var User = mongoose.model('User');
var passport = require('passport');
var jwt = require('express-jwt');
var auth = jwt({secret:'SECRET', userProperty:'payload'});

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.post('/login', function(req, res, next){
	if(!req.body.username || !req.body.password){
		return res.status(400).json({message:' Please fill out all fields'});
	}
	
	passport.authenticate('local', function(err, user, info){
		if(err) return next(err);
		
		if(user){
			return res.json({token: user.generateJWT(), _id : user._id});
		} else {
			return res.status(401).json(info);
		}
	})(req, res, next);
});

router.post('/register', function(req, res, next){
	if(!req.body.username || !req.body.password){
		res.status(400).json({message: 'Please fill out all fields'});
	}
	
	var user = new User();
	
	user.username = req.body.username;
	user.setPassword(req.body.password);
	user.numberPosts = 0;
	user.save(function(err){
		if(err)	return next(err);
		
		return res.json({token:user.generateJWT()});
	});
});

router.param('userid', function(req, res, next, id){
	var query = User.findById(id);
	
	query.exec(function(err, user){
		if(err)
			return next(err);
		
		if(!user)
			return next(new Error("can\'t find user"));
		
		req.user = user;
		return next();
	});
});

router.get('/:userid/posts', auth, function(req, res, next){
	var data = {};
	data.numberPosts = req.user.numberPosts;
	
	var options = {
			path : 'posts',
			options: {sort:{date:-1}}
	};
	req.user.populate(options).exec(function(err, posts){
		if(err){
			return next(err);
		}
		
		data.posts = posts;
		console.log("posts : " + data.posts);
		res.json(data);
	});
});

router.post('/:userid/posts/newpost', auth, function(req, res, next){
	Post.create({
		title:req.body.title,
		body:req.body.body,
		date: Date.now(),
		userid: req.user._id
	}, function(err, newpost){
		req.user.comments.push(newpost);
		req.user.numberPosts += 1;
		req.user.save(function(err, updatedUser){
			if(err) return next(err);
			
			res.json(updateUser);
		});
	});
});

router.get('/:userid/posts/:postid/', auth, function(req, res, next){
	
});


module.exports = router;
