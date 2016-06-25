var mongoose = require('mongoose');

var PostSchema = new mongoose.Schema({
	title: String,
	body: String,
	date: Date,
	userid: [{type:mongoose.Schema.Types.ObjectId, ref: 'User' }]
});

mongoose.model('Post', PostSchema);