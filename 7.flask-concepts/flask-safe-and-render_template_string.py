# I'm working on my website with Flask and Jinja templates, and I have an odd bug about including images in templates. I have a post.html template that inherits from a base.html, and it gets passed a post object from an SQL database. The problem is that some of the Jinja templating functions don't get called when I do so, namely image HTML tags don't load correctly based on the url_for() call. Regular HTML tags are fine, as I use |safe to make they get processed.

# Example from the post.html template:

{% extends "base.html" %}
{% block content %}
<div class="post-description">
        <p>
            {{post.body|safe}}       
        </p>
</div>
{% endblock %}

# Example from that post.body call:

<b> I work, and am bolded</b>
<img src="{{ url_for('static', filename = 'images/randomImg.png') }}">

# While the bold text shows up fine, the url_for is never called. In the outputted source (on the actual website), it's easy to verify, as the src link is never properly represented, unlike other pages where the function is evaluated. If I copy/paste the <img> line so that now my post.html looks like:

{% extends "base.html" %}
{% block content %}
<div class="post-description">
        <p>
            <img src="{{ url_for('static', filename = 'images/randomImg.png') }}">
            {{post.body|safe}}       
        </p>
</div>
{% endblock %}

# The first image call loads fine, but the one's inside post.body do not. I'm not sure if there's a Flask or Jinja way to force it to evaluate it, but I'm hoping so.

# Edit Solution: The trick was to first render the post.body inside a call to render_template_string, as that will properly "fill out" the url_for calls so that render_template can then evaluate properly.

# post.body was not processed the way you want it, because jinja2 does not try to rerender its own output by default, which makes perfect sense.

# You could render the post body and then render response:

@app.route("/some/path")
def some_view():
    # ...
    post = Post.query.first()
    rendered_post_body = render_template_string(post.body)
    return render_template("some_template.html", post_body=rendered_post_body)