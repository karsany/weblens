<script>
    import Logo from "./Logo.svelte";
</script>

<nav>
    <div class="nav-left">
        <Logo size="32" />
        <span class="brand"> WebLens </span>
    </div>
    <div class="nav-right">
        <a class="button" href="/">Dashboard</a>
        <a class="button" href="/user">User settings</a>
        <a class="button" href="/photo">Test</a>
    </div>
</nav>
