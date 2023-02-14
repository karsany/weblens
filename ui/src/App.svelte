<script>
	import Nav from "./components/Nav.svelte";
	import Dashboard from "./pages/Dashboard.svelte";
	import Photo from "./pages/Photo.svelte";
	import User from "./pages/User.svelte";

	import router from "page";

	let page;

	router("/", () => (page = Dashboard));
	router("/user", () => (page = User));
	router("/photo", () => (page = Photo));

	router.start();
</script>

<header>
	<Nav />
</header>

<div class="container">
	<main>
		<svelte:component this={page} />
	</main>
</div>

<footer class="main">
	<p>weblens - <a href="https://github.com/karsany/weblens">github</a></p>
</footer>

<style>
</style>
