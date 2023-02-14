<script>
    function captureAndRefresh() {
        status = false;
        url = "";
        fetch("/api/photo/capture")
            .then((response) => {
                console.log(response);
                return response.json();
            })
            .then((data) => {
                setTimeout(function () {
                    status = true;
                    counter++;
                    url = "/api/photo/download?q=" + counter;
                }, 2000);
            });
    }

    let counter = 0;
    let status = true;
    let url = "";
</script>

<div class="card">
    <header>Test picture</header>
    <footer class="is-right">
        <button on:click={captureAndRefresh}>Capture</button>
    </footer>
    <div class="pic">
        {#if status == true}
            <img src={url} alt="Last camera capture" width="100%" />
        {/if}
    </div>
</div>

<style>
    .pic {
        border: 2px solid black;
        height: 480px;
        width: 640px;
        margin: 0 auto;
    }
</style>
